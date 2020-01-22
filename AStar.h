//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Searcher.h"
#include <map>

template<typename S, typename T>

class AStar : public Searcher<S, T> {
public:

    map<State<T> *, int> open;

    map<State<T> *, int> closed;

    State<T> *least;

    void initialize();

    void setLeast(State<T> *s) {
        this->least = s;
    }

    State<T> *findLeast(State<T> *s1, State<T> *s2) {
        if (s1->getCost() < s2->getCost()) {
            return s1;
        }
        return s2;
    }

    bool isInOpen(State<T> *key) {
        auto it = open.find(key);
        return it != open.end();
    }

    bool isInClosed(State<T> *key) {
        auto it = closed.find(key);
        return it != closed.end();
    }

    int calculateCost(int cost, int trailCost) {
        return cost + trailCost;
    }


    AStar() = default;

    S search(Searchable<T> *searchable) {

    }

    ~AStar() = default;

};

#endif //EX4_ASTAR_H
