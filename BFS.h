//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__BFS_H_
#define EX4__BFS_H_

//#include <bits/basic_string.h>
#include <vector>
#include <string>
#include "Searchable.h"
#include "Matrix.h"
#include "Searcher.h"

using namespace std;

template<typename S, typename T>
class BFS : public Searcher<S, T> {
 public:
  BFS();
  string findPath(vector<vector<pair<int, int>>> graph, pair<int, int> dest);
  string search(Searchable<T> *state);
};

#endif //EX4__BFS_H_