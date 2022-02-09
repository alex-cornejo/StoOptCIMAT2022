//
// Created by alex on 26/05/20.
//

#ifndef CKC_CPP_UTILS_H
#define CKC_CPP_UTILS_H

#include <vector>
#include <tuple>
#include "../FAPSolver.h"

class FileUtil {

public:
    static std::vector<std::vector<std::tuple<int, int, int>>> load_adj(const std::string &file_path, int n);

    static bool save(std::string &output_path, std::string &content);

    static std::pair<std::vector<FAP_edge>, int> load_edges(const std::string &file_path, int m);

    static int check_number_lines(const std::string &file);
};


#endif //CKC_CPP_UTILS_H
