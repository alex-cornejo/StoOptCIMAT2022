//
// Created by ale_j on 2/7/2022.
//

#include <iostream>
#include "HEDGE.h"

using namespace std;


std::vector<int> HEDGE::run() {
    vector<int> individual(n);
    long fitness = 0;

    // all are marked as unassigned
    fill(individual.begin(), individual.end(), -1);

    for (int i = 0; i < n; ++i) {

        // assign a frequency to max degree vertex
        int min_pij = numeric_limits<int>::max();
        int c;
        for (int ci = 0; ci < F; ++ci) {
            int pij = 0;
            for (auto &adj_j: adj[max_degree_v]) {
                int data_j;
                int data_dij;
                int data_pij;
                tie(data_j, data_dij, data_pij) = adj_j;
                if (individual[data_j] != -1) {
                    int z = abs(ci - individual[data_j]);
                    if (abs(ci - individual[data_j]) <= data_dij) {
                        pij += data_pij;
                    }
                }
            }
            if (pij < min_pij) {
                min_pij = pij;
                c = ci;
            }
        }
        fitness += min_pij;
        individual[max_degree_v] = c;
        marked[max_degree_v] = true;

        // remove vertex from Gs
        max_degree_v = update_Gs(max_degree_v);
    }
    cout << fitness << endl;
    return individual;
}

int HEDGE::update_Gs(int v) {
    FAP_edge sv{};
    sv.j = v;
    int max_degree = -1;
    int u;
    for (int i = 0; i < n; ++i) {
//        if (Gs[i].find(sv) != Gs[i].end()) {
//            Gs[i].erase(sv);
//        }
        Gs[i].erase(sv);

        if (!marked[i] && (int) Gs[i].size() > max_degree) {
            max_degree = Gs[i].size();
            u = i;
        }
    }
    return u;
}

HEDGE::HEDGE(int n, int f, std::vector<std::vector<std::tuple<int, int, int>>> &adj) : n(n), F(f), adj(adj) {
    marked.resize(n);

    // init Gs
    int max_degree = -1;
    Gs.resize(n);
    for (int i = 0; i < n; ++i) {
        Gs[i].reserve(adj[i].size());
        int degree = adj[i].size();
        if (max_degree < degree) {
            max_degree = degree;
            max_degree_v = i;
        }

        for (auto &data: adj[i]) {
            FAP_edge sv{};
            tie(sv.j, sv.dij, sv.pij) = data;
            Gs[i].insert(sv);
        }
    }
}