//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__MATRIX_H_
#define EX4__MATRIX_H_


#include <vector>
#include "Cell.h"
#include "Searchable.h"

using namespace std;


class Matrix : Searchable<Cell *> {
public:
    Matrix(vector<vector<int>> mat);

    void initMatrix(vector<vector<int>> mat);

    int getRowNum();

    int getColNum();

    vector<vector<Cell *>> getMatrix();

    bool isInRange(int row, int col);

    bool isUnBlocked(int row, int col);

    ~Matrix() = default;

private:
    int rows;
    int cols;
    vector<vector<Cell *>> matrix;
};


#endif //EX4__MATRIX_H_