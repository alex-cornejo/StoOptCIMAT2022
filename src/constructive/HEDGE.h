//
// Created by ale_j on 2/7/2022.
//

#ifndef STOOPT_HEDGE_H
#define STOOPT_HEDGE_H


#include <vector>
#include <set>
#include <unordered_set>
#include "../FAPSolver.h"

class HEDGE {
private:
    int n;
    int F;
    int max_degree_v;
    std::vector<bool> assigned;
    std::vector<std::vector<FAP_edge>> &adj;
    std::vector<std::unordered_set<FAP_edge, FAP_edge_hash>> Gs;

    int update_Gs(int u);

public:

    HEDGE(int n, int f, std::vector<std::vector<FAP_edge>> &adj);

    std::vector<int> run();

    int create_Gs();
};


#endif //STOOPT_HEDGE_H
