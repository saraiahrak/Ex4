//
// Created by dekel on 15/01/2020.
//

#ifndef EX4__STRINGREVERSER_H_
#define EX4__STRINGREVERSER_H_

#include "Solver.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    //Constructor
    StringReverser();

    //Default destructor
    ~StringReverser() = default;

    string getName() override;

    string solve(string s) override;

    StringReverser* clone() override {
        return new StringReverser();
    }

private:
    string id;
};

#endif //EX4__STRINGREVERSER_H_