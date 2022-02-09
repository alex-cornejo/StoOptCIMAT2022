//
// Created by ale_j on 1/21/2022.
//

#ifndef STOOPT_FAPSOLVER_H
#define STOOPT_FAPSOLVER_H

#include <vector>

struct FAP_edge {
    int i;
    int j;
    int dij;
    int pij;

    bool operator==(const FAP_edge &u) const {
        return j == u.j;
    }

    bool operator<(const FAP_edge &u) const {
        return j < u.j;
    }

    bool operator>(const FAP_edge &u) const {
        return j > u.j;
    }

    size_t operator()(const FAP_edge &p) const {
        return std::hash<uint32_t>()(p.j);
    }

};

struct FAP_edge_hash {
public:
    size_t operator()(const FAP_edge e) const {
        return std::hash<uint32_t>()(e.j);
    }
};

class FAPSolver {
private:
    std::vector<FAP_edge> edges;
    int m;
    int n;
    int F;
    int pop_size;
    std::vector<std::vector<FAP_edge>> adj;

    long evaluate(std::vector<int> &ind);

    std::vector<std::vector<int>> generate_pop();

public:
    std::vector<std::pair<int, int>> generate_full_neighborhood();

    long run_swaplocalsearch(std::vector<int>& individual);

    long run_circularlocalsearch(std::vector<int>& individual);

    FAPSolver(std::vector<FAP_edge>& edges, std::vector<std::vector<FAP_edge>> &adj, int m, int n, int f, int popSize);

    virtual ~FAPSolver();

    long swap_localsearch(std::vector<int> &individual);

    long incremental_evaluator(std::vector<int> &individual, std::pair<int, int> &neighbor);

    long run_random_search();

    std::vector<int> create_randomindividual();

    long circular_localsearch(std::vector<int> &individual);
};


#endif //STOOPT_FAPSOLVER_H
