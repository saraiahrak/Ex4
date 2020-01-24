//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_OBJECTADAPTER_H
#define EX4_OBJECTADAPTER_H

#include "Solver.h"
#include "Searcher.h"
#include "Matrix.h"

using namespace std;

class ObjectAdapter : public Solver<string, string> {
public:
    string initial;
    string dest;
    Searcher<string, Cell *> *searcher;

    ObjectAdapter(Searcher<string, Cell *> *s);

    Matrix *createSearchable(string problem);

    vector<vector<int>> createVector(string problem);

    string solve(string problem) override;

    //Default destructor
    ~ObjectAdapter() = default;

    Searcher<string, Cell *> *getSearcher();

    string getName();

    ObjectAdapter *clone() {
        return new ObjectAdapter(this->searcher->clone());
    }
};

#endif //EX4_OBJECTADAPTER_H
