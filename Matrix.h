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

    void initMatrix(vector<vector<int>> mat);

    int getRowNum();

    int getColNum();

    vector<vector<Cell *>> getMatrix();

    void setInitialState(State<Cell *> *s);

    void setDestState(State<Cell *> *s);

    static State<Cell *> *createInitialState();

    State<Cell *> *createDestState();

    State<Cell *> *getInitialState() override;

    bool isGoalState(State<Cell *> *s) override;

    void setNewSearch(State<Cell *> *entry, State<Cell *> *dest);

    vector<State<Cell *> *> getAllPossibleStates(State<Cell *> *currentState) override;

    Cell* getCell(int row, int col);

    bool isInRange(int row, int col);

    bool isUnBlocked(int row, int col);

    ~Matrix() = default;

private:
    int rows;
    int cols;
    vector<vector<Cell *>> matrix;
    State<Cell *> *initCell;
    State<Cell *> *destCell;
};


#endif //EX4__MATRIX_H_