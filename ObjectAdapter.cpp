//
// Created by sarai on 21/01/2020.
//

#include "ObjectAdapter.h"
#include "Utils.h"

using namespace std;

ObjectAdapter::ObjectAdapter(Searcher<string, Cell *> *s) {
    this->searcher = s;
}

ObjectAdapter::ObjectAdapter(string i, string d) {
  this->initial = i;
  this->dest = d;
}


string ObjectAdapter::solve(string problem) {
    return searcher->search(createSearchable(problem));
}

Matrix *ObjectAdapter::createSearchable(string matrix) {
  Matrix* m = new Matrix(createVector(matrix));
  vector<string> initialVec = Utils::splitByDelim(this->initial, ",");
  vector<string> destlVec = Utils::splitByDelim(this->dest, ",");

  m->setNewSearch(stoi(initialVec[0]), stoi(initialVec[1]),
      stoi(destlVec[0]), stoi(destlVec[1]));
  return m;
}

vector<vector<int>> ObjectAdapter::createVector(string problem) {
    vector<vector<int>> matrix;
    vector<int> currentRow;
    vector<string> stringRows = Utils::splitByDelim(problem, "\n");

    this->initial = stringRows.at(stringRows.size() - 2);
    this->dest = stringRows.at(stringRows.size() - 1);

    stringRows.erase(stringRows.end() - 1);
    stringRows.erase(stringRows.end() - 1);

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
