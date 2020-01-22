//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_STATECOMPARATOR_H
#define EX4_STATECOMPARATOR_H

#include "State.h"

template<typename T>
class StateComparator {

public:
    int operator()(State<T> *s1, State<T> *s2) {
        return s1->getCost() > s2->getCost();
    }
};

#endif //EX4_STATECOMPARATOR_H
