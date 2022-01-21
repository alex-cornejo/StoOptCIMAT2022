#include <iostream>
#include "utils/FileUtil.h"

using namespace std;

long evaluate(vector<int> &ind, vector<vector<tuple<int, int, int>>> &adj) {
    long fitness = 0;
    int iv = 0;
    for (auto &v_adj: adj) {
        for (auto &neighbor: v_adj) {
            int iu, dvu, puv;
            tie(iu, dvu, puv) = neighbor;
            if (abs(ind[iv] - ind[iu]) <= dvu) {
                fitness += puv;
            }
        }
        iv++;
    }
    return fitness;
}

vector<vector<int>> generate_pop(int pop_size, int n, int F) {
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

long get_best(vector<vector<int>> &pop, vector<vector<tuple<int, int, int>>> &adj) {
    long best_fitness = INT64_MAX;
    for (auto &ind: pop) {
        best_fitness = min(best_fitness, evaluate(ind, adj));
    }
    return best_fitness;
}

int main() {

    string input_file = "";
    int F = 0;
    int seed = 0;
    string output_file = "";

    int n = 272;
    F = 39;
    std::string file = "/mnt/d/Users/ale_j/Documents/inaoe/repos/StoOpt/FAP08/GSM2-272.ctr";
    vector<vector<tuple<int, int, int>>> adj = FileUtil::load_graph(file);
    srand(seed);
    auto pop = generate_pop(100000, n, F);
    long best = get_best(pop, adj);
    cout << best << endl;

    return 0;
}
