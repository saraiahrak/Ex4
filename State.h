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
        this->value = st;
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

    bool isEqual(State<T> *s) {
        return value.isEqual(s->value);
    }

    T getStateStruct() {
        return this->state;
    }

private:

    int cost;

    int trailCost;

    State<T> *prev;

    T value;

};

#endif //EX4_STATE_H
