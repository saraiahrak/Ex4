//
// Created by dekel on 15/01/2020.
//


#include "StringReverser.h"

using namespace std;

//reverse the given string
string StringReverser::solve(string problem) {
    string solution;
    reverse(problem.begin(), problem.end());
    auto it = problem.begin();
    for (; it != problem.end(); ++it) {
        solution += *it;
    }
    return solution;
}

StringReverser::StringReverser() {
    this->id = "Reverse";
}

string StringReverser::getName() {
    return this->id;
}