//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_OBJECTADAPTER_H
#define EX4_OBJECTADAPTER_H

#include "Solver.h"
#include "Searcher.h"
#include "Matrix.h"

using namespace std;

class ObjectAdapter : public Solver<vector<vector<int>>, string> {
public:
    ObjectAdapter(Searcher<string, Cell *> *s);

    Searcher<string, Cell *> *searcher;

    static Matrix *createSearchable(vector<vector<int>> mat);

    string solve(vector<vector<int>> problem) override;

    ~ObjectAdapter() = default;


};

#endif //EX4_OBJECTADAPTER_H
