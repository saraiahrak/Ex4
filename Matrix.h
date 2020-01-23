//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__MATRIX_H_
#define EX4__MATRIX_H_


#include <vector>
#include "Cell.h"
#include "Searchable.h"

using namespace std;


class Matrix : public Searchable<Cell *> {
public:
    Matrix(vector<vector<int>> mat);

    State<Cell *> *getDestState() override;

    void initMatrix(vector<vector<int>> mat);

    int getRowNum();

    int getColNum();

    vector<vector<Cell *>> getMatrix();

    void setInitialState(int row, int col);

    void setDestState(int row, int col);

    State<Cell *> *getInitialState() override;

    bool isGoalState(State<Cell *> *s) override;

    void setNewSearch(int initRow, int initCol, int destRow, int destCol);

    vector<State<Cell *> *> getAllPossibleStates(State<Cell *> *currentState) override;

    Cell *getCell(int row, int col);

    bool isInRange(int row, int col);

    bool isUnBlocked(int row, int col);

    string to_string();

    ~Matrix() = default;

    State<Cell *> *getState(int row, int col);

private:
    int rows;
    int cols;
    vector<vector<Cell *>> matrix;
    vector<vector<State<Cell *> *>> states;
    State<Cell *> *initCell;
    State<Cell *> *destCell;
};


#endif //EX4__MATRIX_H_