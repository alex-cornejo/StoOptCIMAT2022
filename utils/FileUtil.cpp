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

using namespace std;

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

vector<vector<tuple<int, int, int>>> FileUtil::load_graph(const std::string &file_path) {

    int n = 272;
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

int **FileUtil::load_edges(const std::string &file_path, int m) {
    int **edges;
    int n = 272;
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
    return edges;
}

bool FileUtil::save(std::string &output_path, std::string &content) {
    std::ofstream output_file(output_path);
//    output_file.write(&content, content.size());
    output_file << content;
    output_file.close();
    return true;
}
