//
// Created by sarai on 21/01/2020.
//

#include "ObjectAdapter.h"

using namespace std;

ObjectAdapter::ObjectAdapter(Searcher<string, Cell *> *s) {
    this->searcher = s;
}

string ObjectAdapter::solve(vector<vector<int>> problem) {
    return searcher->search(createSearchable(problem));
}

Matrix *ObjectAdapter::createSearchable(vector<vector<int>> matrix) {
    return new Matrix(matrix);
}
