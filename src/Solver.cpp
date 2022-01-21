//
// Created by ale_j on 1/21/2022.
//

#include <cstdlib>
#include <cstdint>
#include "Solver.h"

using namespace std;

std::vector<std::vector<int>> Solver::generate_pop() {
    vector<vector<int>> pop(pop_size);
    for (int i = 0; i < pop_size; ++i) {
        vector<int> ind(n);
        for (int j = 0; j < n; j++) {
            ind[j] = rand() % F;
        }
        pop[i] = ind;
    }
    return pop;
}

long Solver::run() {

    vector<std::vector<int>> pop = generate_pop();
    long best_fitness = INT64_MAX;
    for (auto &ind: pop) {
        best_fitness = min(best_fitness, evaluate(ind));
    }
    return best_fitness;
}

long Solver::evaluate(vector<int> &ind) {
    long fitness = 0;

    for (int i = 0; i < m; ++i) {
        int v = edges[i][0];
        int u = edges[i][1];
        int dvu = edges[i][2];
        int pvu = edges[i][3];

        if (abs(ind[v] - ind[u]) <= dvu) {
            fitness += pvu;
        }
    }
    return fitness;
}

Solver::Solver(int **edges, int m, int n, int f, int popSize) : edges(edges), m(m), n(n), F(f), pop_size(popSize) {}

Solver::~Solver() {
    for (int i = 0; i < m; i++) {
        delete[] edges[i];
    }
    delete[] edges;
}
