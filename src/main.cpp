#include <iostream>
#include <sstream>
#include "./utils/FileUtil.h"
#include "FAPSolver.h"
#include "constructive/HEDGE.h"

using namespace std;


long evaluate(vector<int> &ind, const vector<FAP_edge> &edges) {
    long fitness = 0;

    for (FAP_edge e: edges) {
        if (abs(ind[e.i] - ind[e.j]) <= e.dij) {
            fitness += e.pij;
        }
    }
    cout << "Fitness: " << fitness << endl;
}

int main(int argc, char **argv) {

    // read parameters
    if (argc != 5) {
        cout << "Wrong parameters!" << endl;
    }
    string input_file = argv[1];
    int F = atoi(argv[2]);
    int seed = atoi(argv[3]);
    string output_file = argv[4];

    int m = FileUtil::check_number_lines(input_file);

    int pop_size = 100000;
    vector<FAP_edge> edges;
    int n;
    // load graph
    tie(edges, n) = FileUtil::load_edges(input_file, m);
    vector<vector<tuple<int, int, int>>> adj = FileUtil::load_adj(input_file, n);
    srand(seed);

    // executes algorithm
//    FAPSolver solver(edges, adj, m, n, F, pop_size);
//    long best = solver.run_swaplocalsearch();
//    cout << best << endl;

    HEDGE greedy(n, F, adj);
    vector<int> solution = greedy.run();
    evaluate(solution, edges);

    FAPSolver solver(edges, adj, m, n, F, pop_size);
//    long best = solver.run_swaplocalsearch({solution});
//    long best = solver.run_random_search();
//    cout << best << endl;

    evaluate(solution, edges);

//    // print best solution fitness
//    string s_best = std::to_string(best);
//    FileUtil::save(output_file, s_best);

    return 0;
}
