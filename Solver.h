//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template<typename P, typename S>
class Solver {
public:
    virtual S solve(P problem) = 0;
};

#endif //EX4_SOLVER_H
