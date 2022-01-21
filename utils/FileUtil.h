//
// Created by alex on 26/05/20.
//

#ifndef CKC_CPP_UTILS_H
#define CKC_CPP_UTILS_H

#include <vector>
#include <tuple>

class FileUtil {

public:

    static std::vector<std::vector<std::tuple<int, int, int>>> load_graph(const std::string &file_path);

    static bool save(std::string &output_path, std::string &content);

    int **load_edges(const std::string &file_path, int m);
};


#endif //CKC_CPP_UTILS_H
