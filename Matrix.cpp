//
// Created by dekel on 18/01/2020.
//

#include "Matrix.h"

Matrix::Matrix(vector<vector<int>> mat) {
  this->rows = mat.size();
  this->cols = mat.at(0).size();
  initMatrix(mat);
  setInitialState(0, 0);
  setDestState(rows - 1, cols - 1);
}

void Matrix::initMatrix(vector<vector<int> > mat) {
  vector<vector<Cell *>> cells;
  vector<Cell *> cellRow;
  vector<vector<State<Cell *> *>> allStates;
  vector<State<Cell *> *> rowStates;
  int rowIndex = 0;
  int colIndex = 0;
  for (const vector<int> &row : mat) {
    for (int val : row) {
      cellRow.push_back(new Cell(pair<int, int>(rowIndex, colIndex), val));
      rowStates.push_back(new State<Cell *>(cellRow.at(colIndex)));
      colIndex++;
    }
    cells.push_back(cellRow);
    allStates.push_back(rowStates);
    cellRow.clear();
    rowStates.clear();
    colIndex = 0;
    rowIndex++;
  }

  this->matrix = cells;
  this->states = allStates;
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
    neighbors.push_back(this->getState(row, col + 1));
  }
  if (col > 0) {
    neighbors.push_back(this->getState(row, col - 1));
  }
  if (row < this->rows - 1) {
    neighbors.push_back(this->getState(row + 1, col));
  }
  if (row > 0) {
    neighbors.push_back(this->getState(row - 1, col));
  }

  auto iter = neighbors.begin();
  for (State<Cell *> *neighbor : neighbors) {
    if (neighbor->getValue()->getValue() == -1) {
      neighbors.erase(iter);
    }
    iter++;
  }

  return neighbors;
}

State<Cell *> *Matrix::getInitialState() {
  return this->initCell;
}

void Matrix::setInitialState(int row, int col) {
  this->initCell = getState(row, col);
}

void Matrix::setNewSearch(int initRow, int initCol, int destRow, int destCol) {
  setInitialState(initRow, initCol);
  setDestState(destRow, destCol);
}

void Matrix::setDestState(int row, int col) {
  this->destCell = getState(row, col);
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

State<Cell *> *Matrix::getState(int row, int col) {
  return this->states.at(row).at(col);
}