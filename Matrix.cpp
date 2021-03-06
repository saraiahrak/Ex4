//
// Created by dekel on 18/01/2020.
//

#include "Matrix.h"


//constructor- initializes a matrix and it's cells and states
Matrix::Matrix(vector<vector<int>> mat) {
    this->intMat = mat;
    this->rows = mat.size();
    this->cols = mat.at(0).size();
    initMatrix(mat);
    setInitialState(0, 0);
    setDestState(rows - 1, cols - 1);
    setAllHeur();
}

//initialize a matrix given a matrix vector
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

//check if a given state is the goal state
bool Matrix::isGoalState(State<Cell *> *s) {
    return s->isEqual(this->destCell);
}

//get a cell according to position
Cell *Matrix::getCell(int row, int col) {
    return this->matrix.at(row).at(col);
}

//get all possible "next" state (neighbors) given a state
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

    //remove all infinity cells
    auto iter = neighbors.begin();
    for (int i = 0; i < neighbors.size(); i++) {
        if (neighbors.at(i)->getValue()->getValue() == -1) {
            neighbors.erase(iter + i);
            i--;
        }
    }

    return neighbors;
}

//get the initial state of the searchable matrix
State<Cell *> *Matrix::getInitialState() {
    return this->initCell;
}

//set the initial state to begin the search
void Matrix::setInitialState(int row, int col) {
    this->initCell = getState(row, col);
}

//set a new search given the initial and destination states positions
void Matrix::setNewSearch(int initRow, int initCol, int destRow, int destCol) {
    setInitialState(initRow, initCol);
    setDestState(destRow, destCol);
}

//set destination given the position
void Matrix::setDestState(int row, int col) {
    this->destCell = getState(row, col);
    setAllHeur();
}

//get the matrix
vector<vector<Cell *> > Matrix::getMatrix() {
    return this->matrix;
}

//get number of columns
int Matrix::getColNum() {
    return this->cols;
}

//get number of rows
int Matrix::getRowNum() {
    return this->rows;
}

//get the destination state
State<Cell *> *Matrix::getDestState() {
    return this->destCell;
}

//checks if the point is in the matrix range and returns true if in range, otherwise false
bool Matrix::isInRange(int r, int c) {
    return (r >= 0) && (r < this->rows) && (c >= 0) && (c < this->cols);
}

//checks if the point is unblocked and returns true if unblocked, otherwise false
bool Matrix::isUnBlocked(int r, int c) {
    return (matrix.at(r).at(c)->getValue() != -1);
}

//convert to string
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

//get a state given it's position in matrix
State<Cell *> *Matrix::getState(int row, int col) {
    return this->states.at(row).at(col);
}

//set all heuristic values of states
void Matrix::setAllHeur() {
    for (auto row : states) {
        for (auto state : row) {
            state->setHeuristic(calculateHeur(state));
        }
    }
}

//set heuristic value of given state according to Grid optimal function- Manhattan Distance
int Matrix::calculateHeur(State<Cell *> *s) {
    int dx = this->destCell->getValue()->getColPos() - s->getValue()->getColPos();
    int dy = this->destCell->getValue()->getRowPos() - s->getValue()->getRowPos();

    return dx + dy;
}