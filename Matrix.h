//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__MATRIX_H_
#define EX4__MATRIX_H_

#include "Searchable.h"

class Matrix : public Searchable {
public:

    vector<vector<int>> matrix;
    int row;
    int column;

    static struct CurrentNode {
        int row;
        int column;
        int dist;
    };

    Matrix(vector<vector<int>> matrix);

    bool isInRange(int row, int col);

    bool isUnBlocked(int row, int col);

    virtual vector<vector<int>> getMatrix() = 0;

    virtual pair<int, int> getCell() = 0;

};

#endif //EX4__MATRIX_H_
