//
// Created by sarai on 20/01/2020.
//

#ifndef EX4_CELL_H
#define EX4_CELL_H

#include <iostream>


using namespace std;

class Cell {
public:
    Cell(pair<int, int> pos, int val);

    pair<int, int> getPosition();

    int getRowPos();

    int getColPos();

    ~Cell() = default;

private:
    pair<int, int> position;

    int value;


};

#endif //EX4_CELL_H
