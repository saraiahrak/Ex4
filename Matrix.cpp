//
// Created by dekel on 18/01/2020.
//

#include "Matrix.h"

Matrix::Matrix(vector<vector<int>> mat) {
    this->rows = mat.size();
    this->cols = mat.at(0).size();
    setInitialState(createInitialState());
    setDestState(createDestState());
    initMatrix(mat);
}

State<Cell *> *Matrix::createInitialState() {
    auto *state = new State<Cell *>(new Cell(pair<int, int>(0, 0), 0));
    return state;
}

State<Cell *> *Matrix::createDestState() {
    auto *state = new State<Cell *>(new Cell(pair<int, int>(rows - 1, cols - 1), 0));
    return state;
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

bool Matrix::isGoalState(State<Cell *> *s) {
    return s->isEqual(this->destCell);
}

Cell *Matrix::getCell(int row, int col) {
    return this->matrix.at(row).at(col);
}

vector<State<Cell *> *> Matrix::getAllPossibleStates(State<Cell *> *currentState) {

    vector<State<Cell *> *> neighbors;
    int row = currentState->getValue()->getRowPos();
    int col = currentState->getValue()->getColPos();

    if (col < this->cols - 1) {
        neighbors.push_back(new State<Cell *>(getCell(row, col + 1)));
    }
    if (col > 0) {
        neighbors.push_back(new State<Cell *>(getCell(row, col - 1)));
    }
    if (row < this->rows - 1) {
        neighbors.push_back(new State<Cell *>(getCell(row + 1, col)));
    }
    if (row > 0) {
        neighbors.push_back(new State<Cell *>(getCell(row - 1, col)));
    }

    return neighbors;
}

State<Cell *> *Matrix::getInitialState() {
    return this->initCell;
}

void Matrix::setInitialState(State<Cell *> *s) {
    this->initCell = s;
}

void Matrix::setNewSearch(State<Cell *> *entry, State<Cell *> *dest) {
    setInitialState(entry);
    setDestState(dest);
}

void Matrix::setDestState(State<Cell *> *s) {
    this->destCell = s;
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
    return (r >= 0) && (r < this->rows) && (c >= 0) && (c < this->cols);
}


//checks if the point is unblocked and returns true if unblocked, otherwise false
bool Matrix::isUnBlocked(int r, int c) {
    return (matrix.at(r).at(c)->getValue() != -1);
}

string Matrix::to_string() {
    string mat = "";
    int index = 0;
    for (vector<Cell *> row : this->matrix) {
        for (Cell *cell: row) {
            string val = std::to_string(cell->getValue());
            mat += val;
            if (index < row.size() - 1) {
                mat += ",";
            }
            index++;
        }
        mat += "\n";
        index = 0;
    }

    return mat;
}
