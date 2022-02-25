#include <iostream>
#include <sstream>
#include <cstring>
#include "./utils/FileUtil.h"
#include "FAPSolver.h"
#include "constructive/HEDGE.h"

using namespace std;


#include <chrono>

using namespace std::chrono;


long evaluate(vector<int> &ind, vector<FAP_edge> &edges) {
    long fitness = 0;

    for (FAP_edge &e: edges) {
        if (abs(ind[e.i] - ind[e.j]) <= e.dij) {
            fitness += e.pij;
        }
    }
    cout << "Fitness: " << fitness << endl;
    return fitness;
}

void execute(vector<FAP_edge> &edges, vector<vector<FAP_edge>> &adj, int n, int m, int F, int pop_size,
             string &construction, string &localsearch, bool restart, string &output_file, bool N_opt) {
    FAPSolver solver(edges, adj, m, n, F, pop_size, N_opt);

    // total time in milliseconds to run (if restart=true)
    long max_time = 3600000;
//    long max_time = 30000;
    long run_time = 0;

    do {
        long time_iteration = 0;
        long time_greedy = 0;

        // start time
        auto start = high_resolution_clock::now();

        // create initial solution
        vector<int> individual;
        if (construction == "random") {
            individual = solver.create_randomindividual();
        }
        if (construction == "HEDGE") {

            HEDGE greedy(n, F, adj);
            individual = greedy.run();
            auto stop_greedy = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop_greedy - start);
            time_greedy = duration.count();
        }

        // apply local search
        long best_fitness;
        if (localsearch == "swap") {
            best_fitness = solver.run_swaplocalsearch(individual);
        } else if (localsearch == "HEDGE") {
            best_fitness = solver.run_circularlocalsearch(individual);
        } else {
            best_fitness = solver.doubletrx_localsearch(individual);
        }

        // finish time
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        time_iteration = duration.count();
        run_time += time_iteration;

        // print best solution fitness and runtimes
        string s_best = std::to_string(best_fitness);
        FileUtil::save_append(output_file, s_best);

        s_best = std::to_string(time_iteration);
        FileUtil::save_append(output_file, s_best);

        if (construction == "HEDGE") {
            s_best = std::to_string(time_greedy);
            FileUtil::save_append(output_file, s_best);
        }

    } while (restart && run_time < max_time);
}


int main(int argc, char **argv) {

    // read parameters
    if (argc != 9) {
        cerr << "Wrong parameters!" << endl;
    }
    string input_file = argv[1];
    int F = atoi(argv[2]);
    int seed = atoi(argv[3]);
    string output_file = argv[4];
    string construction = argv[5];
    string localsearch = argv[6];
    bool restarting = strcmp(argv[7], "true") == 0;
    bool N_opt = strcmp(argv[8], "true") == 0;

    if (construction != "random" && construction != "HEDGE") {
        cerr << "Wrong constructive method!" << endl;
    }

    if (localsearch != "swap" && localsearch != "circular" && localsearch != "doubletrx") {
        cerr << "Wrong local search method!" << endl;
    }

    // remove previous file
    FileUtil::delete_file(output_file);

    int m = FileUtil::check_number_lines(input_file);

    vector<FAP_edge> edges;
    int n;
    // load graph
    tie(edges, n) = FileUtil::load_edges(input_file, m);
    vector<vector<FAP_edge>> adj = FileUtil::load_adj(input_file, n);
    srand(seed);
    const int pop_size = 100000;
    execute(edges, adj, n, m, F, pop_size,
            construction, localsearch, restarting, output_file, N_opt);

    return 0;
}
