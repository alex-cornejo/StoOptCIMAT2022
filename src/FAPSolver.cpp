//
// Created by ale_j on 1/21/2022.
//

#include <cstdlib>
#include <cstdint>
#include <tuple>
#include <iostream>
#include "FAPSolver.h"

using namespace std;

#include <chrono>
#include <algorithm>
#include <set>
#include <numeric>
#include <queue>

using namespace std::chrono;

FAPSolver::FAPSolver(vector<FAP_edge> &edges, vector<vector<FAP_edge>> &adj, int m, int n, int f,
                     int popSize) :
        edges(edges), adj(adj), m(m), n(n), F(f), pop_size(popSize) {}

FAPSolver::~FAPSolver() {}

/**
 * Given the number of nodes (n) and the number of frequencies (F)
 * the full neighborhood of size n*F is computed.
 * @return vector of neighbors. Each neighbor is a pair (v, c)
 * where
 * v: the node of the graph
 * c: the frequency channel to be assigned
 */
vector<pair<int, int>> FAPSolver::generate_full_neighborhood() {
    vector<pair<int, int>> neighborhood(n * F);
    int idx_neighbor = 0;
    for (int idx_trx = 0; idx_trx < n; ++idx_trx) {
        for (int idx_F = 0; idx_F < F; ++idx_F) {
            neighborhood[idx_neighbor++] = make_pair(idx_trx, idx_F);
        }
    }
    return neighborhood;
}


vector<pair<int, int>> FAPSolver::make_double_neighborhood() {
    vector<pair<int, int>> neighborhood(n * 2);
    int idx_neighbor = 0;
    for (int idx_trx1 = 0; idx_trx1 < n; ++idx_trx1) {
        for (int idx_trx2 = 0; idx_trx2 < n; ++idx_trx2) {
            neighborhood[idx_neighbor++] = make_pair(idx_trx1, idx_trx2);
        }
    }
    return neighborhood;
}

long FAPSolver::doubletrx_localsearch(vector<int> &ind) {

    vector<int> N_trxi(n);
    iota(N_trxi.begin(), N_trxi.end(), 0); //become: [0..n-1]
    //random_shuffle(N_trxi.begin(), N_trxi.end());
    vector<bool> explored(n);

//    int last2_j = -1, last1_j = -1;
//    queue<int> tabulist;
    deque<int> tabulist;
    int tabu_size = 4;
    while (!N_trxi.empty()) {
        int i = N_trxi.back();
        explored[i] = true;
        N_trxi.pop_back();

        bool improvement = false;
        int j;
        for (FAP_edge &e: adj[i]) {
            j = e.j;
            if (!explored[j]) {
                // get best assignment for i and j
                auto Nij = compute_best_Nij(ind, i, j, e.dij, e.pij);

                // there is a change (improvement)
                if (Nij.first != ind[i] || Nij.second != ind[j]) {
                    if (j == 92) {
                        int a = 1;
                    }
//                    if (find(tabulist.begin(), tabulist.end(), j) == tabulist.end())
                    if (true)
//                    if (j != last2_j)
                    {
                        if (tabulist.size() == tabu_size) {
                            tabulist.pop_back();
                        }
                        tabulist.push_front(j);

//                        last2_j = last1_j == -1 ? -1 : last1_j;
//                        last1_j = j;

                        improvement = true;

                        // move to neighbor Nij
                        ind[i] = Nij.first;
                        ind[j] = Nij.second;

                        // re-add nodes to the neighborhood
                        // with distance at most 2
                        break;
                    }

                } else {
//                    cout << "No improvement!" << endl;
                }
            }
        }
        // re-add nodes to the neighborhood
        // with distance at most 2
        if (improvement) {
            explored[i] = false;
            N_trxi.push_back(i);
            for (FAP_edge &e1: adj[i]) {
                if (e1.j != j && explored[e1.j]) {
                    explored[e1.j] = false;
                    N_trxi.push_back(e1.j);
                    for (FAP_edge &e2: adj[e1.j]) {
                        if (e2.j != i && explored[e2.j]) {
                            explored[e2.j] = false;
                            N_trxi.push_back(e2.j);
                        }
                    }
                }
            }
            for (FAP_edge &e1: adj[j]) {
                if (e1.j != i && explored[e1.j]) {
                    explored[e1.j] = false;
                    N_trxi.push_back(e1.j);
                    for (FAP_edge &e2: adj[e1.j]) {
                        if (e2.j != j && explored[e2.j]) {
                            explored[e2.j] = false;
                            N_trxi.push_back(e2.j);
                        }
                    }
                }
            }
            int b = (int) N_trxi.size();
            if (b < 272) {
                int a = 1;
            }
            cout << N_trxi.size() << endl;
        } else {
            int a = 1;
        }
    }
    return evaluate(ind);

}

/**
 * Given two vertices i and j, the best assignment (Nij) for such vertices is computed.
 *
 * @param ind
 * @param i
 * @param j
 * @param dij
 * @param pij the penalization to be applied if channels of i and j are close enough.
 * @return
 */
pair<int, int> FAPSolver::compute_best_Nij(vector<int> &ind, int i, int j, int dij, long pij) {

    vector<pair<int, long>> trxi_p_ch(F);
    vector<pair<int, long>> trxj_p_ch(F);

    for (int c = 0; c < F; ++c) {
        trxi_p_ch[c] = make_pair(c, 0);
        trxj_p_ch[c] = make_pair(c, 0);
    }

    evaluate_channels(ind, i, j, trxi_p_ch, trxj_p_ch);


    sort(trxi_p_ch.begin(), trxi_p_ch.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });
    sort(trxj_p_ch.begin(), trxj_p_ch.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    long cj_best = trxj_p_ch[0].second; // used for the lower bounds
    pair<int, int> Nij_best;
    long p_Nij_best = INT64_MAX;

    for (pair<int, long> &trxi: trxi_p_ch) {
        int ci = trxi.first;
        long pi = trxi.second;

        // check if lower bound is worse than best solution
        if (pi + cj_best >= p_Nij_best) {
            break;
        }
        for (pair<int, long> &trxj: trxj_p_ch) {
            int cj = trxj.first;
            long pj = trxj.second;

            // search finishes if there is no conflict
            bool conflict = abs(ci - cj) <= dij;
            long p_Nij = pi + pj + (conflict ? pij : 0);
            if (p_Nij < p_Nij_best) {
                p_Nij_best = p_Nij;
                Nij_best = make_pair(ci, cj);
            }
            if (!conflict) break;
        }
    }
    return Nij_best;
}

void FAPSolver::evaluate_channels(vector<int> &ind, int i, int j, vector<pair<int, long>> &trxi_p_ch,
                                  vector<pair<int, long>> &trxj_p_ch) {

    for (FAP_edge &e: adj[i]) {
        if (e.j != j) {
            int ck = ind[e.j];
            for (int c = ck - e.dij; c <= ck + e.dij; ++c) {
                int mod = (c % F + F) % F;
                trxi_p_ch[mod].second += e.pij;
            }
        }
    }
    for (FAP_edge &e: adj[j]) {
        if (e.j != i) {
            int ck = ind[e.j];

            for (int c = ck - e.dij; c <= ck + e.dij; ++c) {
                int mod = (c % F + F) % F;
                trxj_p_ch[mod].second += e.pij;
            }
        }
    }
}

/**
 * Performs a local search by using the swap approach
 * @param individual to use for local search
 * @return best fitness in local search
 */
long FAPSolver::swap_localsearch(vector<int> &individual) {

    long fitness = evaluate(individual);

    vector<pair<int, int>> neighborhood = generate_full_neighborhood();
    size_t i = neighborhood.size();
    while (i > 0) {

        // choose a random Nj
        int j = rand() % i;
        auto Nj = neighborhood[j];

        long fitness_diff = incremental_evaluator(individual, Nj);

        if (fitness_diff < 0) {
            // Nj improves fitness
            // reset bar
            i = neighborhood.size();

            // move to Nj
            individual[Nj.first] = Nj.second;
            fitness += fitness_diff;
        } else {
            //Nj worse fitness
            // do swap and move bar
            swap(neighborhood[j], neighborhood[--i]);
        }
    }

    return fitness;
}

/**
 * Performs a local search by using the circular approach
 * i.e. it iterates circularly the vector of neighbors
 * until all of them are explored.
 * Iterates to the right.
 *
 * @param individual to use for local search
 * @return best fitness in local search
 */
long FAPSolver::circular_localsearch(vector<int> &individual) {

    long fitness = evaluate(individual);

    vector<pair<int, int>> neighborhood = generate_full_neighborhood();

    int neighborhood_size = (int) neighborhood.size();

    // choose a random neighbor to start
    int i = rand() % neighborhood_size;
    int j = i > 0 ? i - 1 : neighborhood_size - 1;

    while (i != j) {
        auto Ni = neighborhood[i];
        long fitness_diff = incremental_evaluator(individual, Ni);

        if (fitness_diff < 0) {
            // Ni improves fitness
            // reset bar
            j = i;

            // move to that Ni
            individual[Ni.first] = Ni.second;
            fitness += fitness_diff;
        }
        if (++i == neighborhood_size) {
            i = 0;
        }
    }

    return fitness;
}

/**
 * Given an individual and a possible move (neighbor (v, c) v is the node and c the channel),
 * the quality of the move (v, c) is incrementally evaluated by exploring only the possible
 * affected edges if move (v, c) is performed.
 *
 * @param individual
 * @param neighbor move (v, c) to be evaluated
 * @return the difference of penalization if move (v, c) is performed.
 * A negative difference means that move (v, e) decrease penalization (good move)
 * A positive difference means that move (v, e) increase penalization (bad move)
 */
long FAPSolver::incremental_evaluator(vector<int> &individual, pair<int, int> &neighbor) {
    int v = neighbor.first;
    int c = neighbor.second;
    long fitness_diff = 0;
    for (FAP_edge &e: adj[v]) {

        // measure penalization of original channel of v
        if (abs(individual[v] - individual[e.j]) <= e.dij) {
            fitness_diff -= e.pij;
        }
        // measure penalization of move (v, c)
        if (abs(c - individual[e.j]) <= e.dij) {
            fitness_diff += e.pij;
        }
    }
    return fitness_diff;
}

/**
 * Generates a population of individuals (candidate solutions)
 * @return a vector of individuals
 */
std::vector<std::vector<int>> FAPSolver::generate_pop() {
    vector<vector<int>> pop(pop_size);
    for (int i = 0; i < pop_size; ++i) {
        pop[i] = create_randomindividual();
    }
    return pop;
}

/**
 * @return a random individual (vector of int)
 */
vector<int> FAPSolver::create_randomindividual() {
    vector<int> ind(n);
    for (int j = 0; j < n; j++) {
        ind[j] = rand() % F;
    }
    return ind;
}


/**
 * Evaluates a vector of integers that represents a candidate solution (individual)
 * @param ind the individual
 * @return fitness value of individual
 */
long FAPSolver::evaluate(vector<int> &ind) {
    long fitness = 0;
    for (FAP_edge &e: edges) {
        if (abs(ind[e.i] - ind[e.j]) <= e.dij) {
            fitness += e.pij;
        }
    }
    return fitness;
}

// run homework 1
long FAPSolver::run_random_search() {

    // 100k random candidate solutions are generated
    vector<std::vector<int>> pop = generate_pop();

    // solutions are evaluated and best one is obtained
    long best_fitness = INT64_MAX;
    for (auto &ind: pop) {
        best_fitness = min(best_fitness, evaluate(ind));
    }
    return best_fitness;
}

// run homework 2
long FAPSolver::run_swaplocalsearch(vector<int> &individual) {

    // local search
    long best_fitness = swap_localsearch(individual);
    return best_fitness;
}

// run homework 2
long FAPSolver::run_circularlocalsearch(vector<int> &individual) {
    // local search
    long best_fitness = circular_localsearch(individual);
    return best_fitness;
}
