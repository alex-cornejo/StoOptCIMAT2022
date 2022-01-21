#include <iostream>
#include <sstream>
#include "./utils/FileUtil.h"
#include "Solver.h"

using namespace std;


int main(int argc, char **argv) {

    if (argc != 5) {
        cout << "Wrong parameters!" << endl;
    }

    string input_file = argv[1];
    int F = atoi(argv[2]);
    int seed = atoi(argv[3]);
    string output_file = argv[4];

    int m = FileUtil::check_number_lines(input_file);

    int pop_size = 100000;
    int **edges;
    int n;
    tie(edges, n) = FileUtil::load_edges(input_file, m);
    srand(seed);

    Solver solver(edges, m, n, F, pop_size);

    long best = solver.run();
    string s_best = std::to_string(best);
    FileUtil::save(output_file, s_best);

    return 0;
}
