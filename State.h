//
// Created by sarai on 20/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include "Cell.h"

template<class T>

class State {
public:
    explicit State<T>(T st) {
        this->stateInfo = st;
    }

    ~State() = default;

    void setCost(int c) {
        this->cost = c;
    }

    void setTrailCost(int tc) {
        this->trailCost = tc;
    }

    void setPrev(State<T> *s) {
        this->prev = s;
    }

private:
    T getStateStruct() {
        return this->state;
    }

    int cost;

    int trailCost;

    State<T> *prev;

    T stateInfo;

};

#endif //EX4_STATE_H
