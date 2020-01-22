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
    ObjectAdapter(Searcher<string, Cell *> *s);

    Searcher<string, Cell *> *searcher;

    static Matrix *createSearchable(string problem);

    static vector<vector<int>> createVector(string problem);

    string solve(string problem) override;

    ~ObjectAdapter() = default;
};

#endif //EX4_OBJECTADAPTER_H
