//
// Created by sarai on 20/01/2020.
//

#ifndef EX4_SEARCHABLE1_H
#define EX4_SEARCHABLE1_H

#include "State.h"
#include <vector>

using namespace std;

template<typename T>

class Searchable {
public:
    virtual State<T> *getInitialState() = 0;

    virtual bool isGoalState(State<T> *s) = 0;

    virtual vector<State<T> *> getAllPossibleStates(State<T> *currentState) = 0;

};

#endif //EX4_SEARCHABLE1_H
