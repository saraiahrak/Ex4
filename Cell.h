//
// Created by sarai on 20/01/2020.
//

#ifndef EX4_CELL_H
#define EX4_CELL_H

#include <iostream>
#include "State.h"


using namespace std;

class Cell {
public:
    Cell(pair<int, int> pos, int val);

    pair<int, int> getPosition();

    int getValue();

    int getRowPos();

    int getColPos();

    bool isEqual(Cell *c);

    ~Cell() = default;

    Cell* clone() {
        return new Cell(this->position, this->value);
    }

private:
    pair<int, int> position;

    int value;
};

#endif //EX4_CELL_H
