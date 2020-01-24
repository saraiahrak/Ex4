//
// Created by sarai on 21/01/2020.
//

#include "ObjectAdapter.h"
#include "Utils.h"

using namespace std;

//Constructor
ObjectAdapter::ObjectAdapter(Searcher<string, Cell *> *s) {
    this->searcher = s;
}

//solves the given problem by sending the problem to the relevant algorithm
string ObjectAdapter::solve(string problem) {
    return searcher->search(createSearchable(problem));
}

// initial the problem, the source and destination of the solution path and returns the matrix
Matrix *ObjectAdapter::createSearchable(string matrix) {
  Matrix* m = new Matrix(createVector(matrix));
  vector<string> initialVec = Utils::splitByDelim(this->initial, ",");
  vector<string> destlVec = Utils::splitByDelim(this->dest, ",");

  m->setNewSearch(stoi(initialVec[0]), stoi(initialVec[1]),
      stoi(destlVec[0]), stoi(destlVec[1]));
  return m;
}

//creates a new matrix from the given problem
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

//returns the Algorithm's ID
string ObjectAdapter::getName() {
    return this->searcher->getId();
}

//returns the searcher for the problem
Searcher<string, Cell *> * ObjectAdapter::getSearcher() {
    return this->searcher;
}
