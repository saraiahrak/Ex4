//
// Created by sarai on 20/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searchable.h"

template<typename S, typename T>


//the algorithms should set the trailcost when choosing a next state, set prev etc.

class Searcher {
    virtual S search(Searchable<T> *searchable) = 0;
};

#endif //EX4_SEARCHER_H
