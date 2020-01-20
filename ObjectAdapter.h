//
// Created by sarai on 20/01/2020.
//

#ifndef EX4_OBJECTADAPTER_H
#define EX4_OBJECTADAPTER_H

#include "Solver.h"
#include "Searcher.h"

using namespace std;

template<typename P, typename S, typename T>

class ObjectAdapter : public Solver<P, S> {
public:
    Searcher<P, S>* searcher;
    S solve(P problem);


};

#endif //EX4_OBJECTADAPTER_H
