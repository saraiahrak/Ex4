//
// Created by sarai on 22/01/2020.
//

#ifndef EX4_ASTARCOMPARATOR_H
#define EX4_ASTARCOMPARATOR_H


#include "State.h"

template<typename T>

//AStar comparator
class AStarComparator {

public:
    /**
     * overriding the operator method used for priority queue
     * to be used for logic of order in the AStar algorithm, according to the
     * heuristic value and trail cost.
     * */
    int operator()(State<T> *s1, State<T> *s2) {
        return s1->getTrailCost() + s1->getHeuristic() > s2->getTrailCost() + s2->getHeuristic();

    }
};


#endif //EX4_ASTARCOMPARATOR_H
