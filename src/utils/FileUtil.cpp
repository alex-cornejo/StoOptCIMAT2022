//
// Created by alex on 26/05/20.
//

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "FileUtil.h"
#include "../FAPSolver.h"

using namespace std;

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

vector<vector<tuple<int, int, int>>> FileUtil::load_adj(const std::string &file_path, int n) {

    vector<vector<tuple<int, int, int>>> adj(n);
    string line;
    ifstream file(file_path);
    vector<std::pair<int, int>> edges_vec;
    if (file.is_open()) {
        while (getline(file, line)) {
            std::string::iterator new_end = std::unique(line.begin(), line.end(), BothAreSpaces);
            line.erase(new_end, line.end());

            boost::trim_right(line);
            boost::trim_left(line);

            vector<std::string> line_vec;
            boost::split(line_vec, line, boost::is_any_of(" "));

            int i = stoi(line_vec[0]);
            int j = stoi(line_vec[1]);
            int dij = stoi(line_vec[4]);
            int pij = stoi(line_vec[5]);
            adj[i].push_back(make_tuple(j, dij, pij));
            adj[j].push_back(make_tuple(i, dij, pij));
        }
        file.close();
    } else {
        cerr << "Unable to open file" << std::endl;
    }
    return adj;
}

pair<vector<FAP_edge>, int> FileUtil::load_edges(const std::string &file_path, int m) {
    vector<FAP_edge> edges(m);

    string line;
    ifstream file(file_path);

    int n = 0;
    int i = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            std::string::iterator new_end = std::unique(line.begin(), line.end(), BothAreSpaces);
            line.erase(new_end, line.end());

            boost::trim_right(line);
            boost::trim_left(line);

            vector<std::string> line_vec;
            boost::split(line_vec, line, boost::is_any_of(" "));

            int v = stoi(line_vec[0]);
            int u = stoi(line_vec[1]);
            int dvu = stoi(line_vec[4]);
            int pvu = stoi(line_vec[5]);

            FAP_edge e{};
            e.i = v;
            e.j = u;
            e.dij = dvu;
            e.pij = pvu;

            edges[i] = e;

            n = max(v, n);
            n = max(u, n);
            i++;
        }
        file.close();
    } else {
        cerr << "Unable to open file" << std::endl;
    }
    return make_pair(edges, n + 1);
}

int FileUtil::check_number_lines(const string &file) {
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(file);

    while (std::getline(myfile, line))
        ++number_of_lines;
    return number_of_lines;
}

bool FileUtil::save(std::string &output_path, std::string &content) {
    std::ofstream output_file(output_path);
    output_file << content << endl;
    output_file.close();
    return true;
}
