//
// Created by sarai on 22/01/2020.
//

#ifndef EX4_ASTARCOMPARATOR_H
#define EX4_ASTARCOMPARATOR_H


#include "State.h"

template<typename T>
class AStarComparator {

public:
    int operator()(State<T> *s1, State<T> *s2) {
        return s1->getCost() + s1->getHeuristic() > s2->getCost() + s1->getHeuristic();
    }
};


#endif //EX4_ASTARCOMPARATOR_H
