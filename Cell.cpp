//
// Created by sarai on 20/01/2020.
//

#include "Cell.h"

using namespace std;

Cell::Cell(pair<int, int> pos, int val) {
    this->value = val;
    this->position = pos;
}

pair<int, int> Cell::getPosition() {
    return position;
}

int Cell::getValue() {
    return this->value;
}

int Cell::getRowPos() {
    return this->position.first;
}

int Cell::getColPos() {
    return this->position.second;
}

bool Cell::isEqual(Cell *c) {
    return c->getPosition() == this->getPosition();
}