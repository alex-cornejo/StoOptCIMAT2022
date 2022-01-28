//
// Created by ale_j on 1/21/2022.
//

#ifndef STOOPT_SOLVER_H
#define STOOPT_SOLVER_H

#include <vector>

class Solver {
private:
    int **edges;
    int m;
    int n;
    int F;
    int pop_size;

    long evaluate(std::vector<int> &ind);

    std::vector<std::vector<int>> generate_pop();

public:
    long run();

    Solver(int **edges, int m, int n, int f, int popSize);

    virtual ~Solver();

};


#endif //STOOPT_SOLVER_H
