//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__SEARCHERSOLVER_H_
#define EX4__SEARCHERSOLVER_H_
#include <string>
#include <vector>
#include "Utils.h"

using namespace std;

class SearcherSolver : public Solver {
  Searcher *searcher;

 public:

  SearcherSolver(Searcher *searcher);

  string solve(vector<string> problem);
};

#endif //EX4__SEARCHERSOLVER_H_
