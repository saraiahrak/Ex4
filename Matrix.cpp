//
// Created by dekel on 18/01/2020.
//

#include "Matrix.h"

//struct CurrentNode;


Matrix::Matrix(vector<vector<int>> mat) {
    this->rows = mat.size();
    this->cols = mat.at(0).size();
    initMatrix(mat);
}

void Matrix::initMatrix(vector<vector<int> > mat) {
    vector<vector<Cell *>> cells;
    vector<Cell *> cellRow;
    int rowIndex = 0;
    int colIndex = 0;
    for (const vector<int> &row : mat) {
        for (int val : row) {
            cellRow.push_back(new Cell(pair<int, int>(rowIndex, colIndex), val));
            colIndex++;
        }
        cells.push_back(cellRow);
        cellRow.clear();
        colIndex = 0;
        rowIndex++;
    }

    this->matrix = cells;
}

vector<vector<Cell *> > Matrix::getMatrix() {
    return this->matrix;
}

int Matrix::getColNum() {
    return this->cols;
}

int Matrix::getRowNum() {
    return this->rows;
}

//checks if the point is in the matrix range and returns true if in range, otherwise false
bool Matrix::isInRange(int r, int c) {
    return (r >= 0) && (r < this->row) && (c >= 0) && (c < this->column);
}


//checks if the point is unblocked and returns true if unblocked, otherwise false
bool Matrix::isUnBlocked(int r, int c) {
    return (matrix[r][c] != -1);
}
