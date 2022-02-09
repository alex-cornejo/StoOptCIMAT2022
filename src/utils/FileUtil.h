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
    static std::vector<std::vector<FAP_edge>> load_adj(const std::string &file_path, int n);

    static bool save_override(std::string &output_path, std::string &content);

    static std::pair<std::vector<FAP_edge>, int> load_edges(const std::string &file_path, int m);

    static int check_number_lines(const std::string &file);

    static bool save_append(std::string &output_path, std::string &content);

    static bool delete_file(std::string &file_path);
};


#endif //CKC_CPP_UTILS_H
