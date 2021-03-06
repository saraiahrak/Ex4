//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_STATECOMPARATOR_H
#define EX4_STATECOMPARATOR_H

#include "State.h"

template<typename T>
class StateComparator {

public:
    /**
        * overriding the operator method used for priority queue
        * to be used for logic of order in the BestFS algorithm, according to the
        * trail cost.
        * */    int operator()(State<T> *s1, State<T> *s2) {
        return s1->getTrailCost() > s2->getTrailCost();
    }
};

#endif //EX4_STATECOMPARATOR_H
