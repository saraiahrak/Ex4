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

    ObjectAdapter(Searcher<string, Cell *> *s);

    ObjectAdapter(string i, string d);

    Searcher<string, Cell *> *searcher;

    Matrix *createSearchable(string problem);

    vector<vector<int>> createVector(string problem);

    string solve(string problem) override;

    ~ObjectAdapter() = default;

    ObjectAdapter* clone() {
      return new ObjectAdapter(this->initial, this->dest);
    }
};

#endif //EX4_OBJECTADAPTER_H
