//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__SEARCHABLE_H_
#define EX4__SEARCHABLE_H_

#include <vector>

using namespace std;

class Searchable {
 public:
  //current location structure of the current row, column and distance from the source

  virtual bool isValid(int row, int col) = 0;

  virtual bool isUnBlocked(int row, int col) = 0;

  virtual vector<vector<int>> getAllPossibleStates() = 0;

  virtual pair<int, int> getInitialState() = 0;

};

#endif //EX4__SEARCHABLE_H_
