//
// Created by ale_j on 2/7/2022.
//

#include <iostream>
#include "HEDGE.h"

using namespace std;

/**
 * Creates an individual (vector of ints) for the FAP
 * by using the Highest Degree-based Greedy Algorithm (HEDGE) heuristic.
 *
 * B. Koo, H. B. Yilmaz, C. Chae, H. Park, J. Ham and S. Park,
 * "Heuristics for frequency assignment problem with realistic interference constraints,"
 * 2016 IEEE International Conference on Communications (ICC), 2016, pp. 1-6,
 * doi: 10.1109/ICC.2016.7510702.
 *
 * @return the individual constructed
 */
std::vector<int> HEDGE::run() {

    vector<int> individual(n);
    long fitness = 0;

    // all are assigned as unassigned
    assigned.resize(n);

    // Step 1: choose vertex of max degree in Gs
    // to add randomness, first vertex is chosen randomly
    max_degree_v = rand() % n;

    for (int i = 0; i < n; ++i) {

        // Step2: assign a frequency channel to max degree vertex
        // the channel to be chosen, is the one that
        // adds less penalization
        long min_pij = numeric_limits<long>::max();
        int c;
        for (int ci = 0; ci < F; ++ci) {
            long pij = 0;
            for (FAP_edge &e: adj[max_degree_v]) {
                if (assigned[e.j] && abs(ci - individual[e.j]) <= e.dij) {
                    pij += e.pij;
                }
            }

            // retain channel c with less penalization
            if (pij < min_pij) {
                min_pij = pij;
                c = ci;
            }
        }
        fitness += min_pij;

        // assigns channel c to vertex of max degree
        individual[max_degree_v] = c;
        assigned[max_degree_v] = true;

        // Step 3: remove vertex with max degree from Gs,
        // update degrees of Gs and choose again a new vertex
        // with max degree
        max_degree_v = update_Gs(max_degree_v);
    }
//    cout<<fitness<<endl;
    return individual;
}

/**
 * Removes a vertex u from the graph Gs
 *
 * @param u vertex to be removed from Gs
 * @return the new vertex with max degree in Gs
 */
int HEDGE::update_Gs(int u) {
    FAP_edge e_2_u{};
    e_2_u.j = u;
    int max_degree = -1;
    int new_max_degree_v;
    for (int i = 0; i < n; ++i) {
        if (!assigned[i]) {
            Gs[i].erase(e_2_u);
            if ((int) Gs[i].size() > max_degree) {
                max_degree = Gs[i].size();
                new_max_degree_v = i;
            }
        }
    }
    return new_max_degree_v;
}

/**
 * Initializes the graph Gs by using a set for each vertex adjacent edges.
 * Set structure is used for quick removals.
 * A vertex v in Gs will be removed after a frequency channel c be assigned
 * to it.
 *
 * @return the vertex of maximum degree in Gs
 */
int HEDGE::create_Gs() {
    int max_degree = -1;
    int max_degree_vertex = -1;
    Gs.resize(n);
    for (int i = 0; i < n; ++i) {
        Gs[i].reserve(adj[i].size());
        int degree = adj[i].size();
        if (max_degree < degree) {
            max_degree = degree;
            max_degree_vertex = i;
        }
        Gs[i].insert(adj[i].begin(), adj[i].end());
    }
    return max_degree_vertex;
}

HEDGE::HEDGE(int n, int f, std::vector<std::vector<FAP_edge>> &adj) : n(n), F(f), adj(adj) {

    // init Gs
    this->max_degree_v = create_Gs();
}
