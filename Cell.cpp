//
// Created by sarai on 20/01/2020.
//

#include "Cell.h"

using namespace std;

//constructor
Cell::Cell(pair<int, int> pos, int val) {
    this->value = val;
    this->position = pos;
}

//get a pair of [row, col] position of cell in matrix
pair<int, int> Cell::getPosition() {
    return position;
}

//get the value of the cell
int Cell::getValue() {
    return this->value;
}

//get the row position
int Cell::getRowPos() {
    return this->position.first;
}

//get the col position
int Cell::getColPos() {
    return this->position.second;
}

//compare to cells according to position
bool Cell::isEqual(Cell *c) {
    return c->getPosition() == this->getPosition();
}