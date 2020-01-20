//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__DFS_H_
#define EX4__DFS_H_
#include <vector>
#include <string>
#include "Searchable.h"
#include "Matrix.h"

using namespace std;

class DFS : public Searcher<vector<vector<int>>> {
public:
    DFS();
    string findPath(vector<vector<pair<int, int>>> parentIndex, pair<int, int> dest);
    string search(Matrix* m, pair<int, int> source, pair<int, int> destination);
};

#endif //EX4__DFS_H_