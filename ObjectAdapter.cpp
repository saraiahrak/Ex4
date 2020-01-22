//
// Created by sarai on 21/01/2020.
//

#include "ObjectAdapter.h"
#include "Utils.h"

using namespace std;

ObjectAdapter::ObjectAdapter(Searcher<string, Cell *> *s) {
    this->searcher = s;
}

string ObjectAdapter::solve(string problem) {
    return searcher->search(createSearchable(problem));
}

Matrix *ObjectAdapter::createSearchable(string matrix) {

    return new Matrix(createVector(matrix));
}

vector<vector<int>> ObjectAdapter::createVector(string problem) {
    vector<vector<int>> matrix;
    vector<int> currentRow;
    vector<string> stringRows = Utils::splitByDelim(problem, "\n");

    for(string row: stringRows) {
        vector<string> elems = Utils::splitByDelim(row, ",");
        for(string elem: elems) {
            int val = stoi(elem);
            currentRow.push_back(val);
        }
        matrix.push_back(currentRow);
        currentRow.clear();
    }

    return matrix;
}
