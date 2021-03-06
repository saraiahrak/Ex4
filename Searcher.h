//
// Created by sarai on 20/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searchable.h"

template<typename S, typename T>


//the algorithms should set the trail cost when choosing a next state, set prev etc.
class Searcher {
public:
    virtual S search(Searchable<T> *searchable) = 0;

    virtual string getId() = 0;

    //duplicate
    virtual Searcher* clone() = 0;
};

#endif //EX4_SEARCHER_H
