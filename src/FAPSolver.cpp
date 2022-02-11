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
