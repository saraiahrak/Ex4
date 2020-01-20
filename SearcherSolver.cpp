//
// Created by dekel on 18/01/2020.
//

#include <cstring>
#include "SearcherSolver.h"
#include "Searchable.h"
#include "Searcher.h"
#include "Matrix.h"

SearcherSolver::SearcherSolver(Searcher* searcher) {
  this->searcher = searcher;
}

//calls the search method of the class member searcher and returns the solution
string SearcherSolver::solve(vector<string> problem) {
  vector<vector<int>> matrix = {};
  for (int i = 0; i < problem.size() - 2; i++) {
    vector<string> s = Utils::splitByDelim(problem[i], ",");
    vector<int> row = {};
    for (int j = 0; j < s.size(); j++) {
      row.push_back(stoi(s[j]));
    }
    matrix.push_back(row);
  }
  Searchable* searchable = new Matrix(matrix);

  //finds the source and destination points
  vector<string> s = Utils::splitByDelim(problem[problem.size() - 2], ",");
  pair<int, int> source = {stoi(s[0]), stoi(s[1])};
  s = Utils::splitByDelim(problem[problem.size() - 1], ",");
  pair<int, int> destination = {stoi(s[0]), stoi(s[1])};

  //if the destination and the source are equal
  if (source.first == destination.first && source.second == destination.second) {
    return "The source and destination are equal";
  }

  //if the points are out of the range of the matrix
  if (!searchable->isValid(source.first, source.second) ||
      !searchable->isValid(destination.first, destination.second)){
    return "Invalid source or destination point";
  }

  //either the source or the destination is blocked
  if (!searchable->isUnBlocked(source.first, source.second) ||
      !searchable->isUnBlocked(destination.first, destination.second)) {
    return "Blocked source or destination";
  }
  //search the problem
  return searcher->search(searchable, source, destination);
}
