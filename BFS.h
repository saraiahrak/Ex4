//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__BFS_H_
#define EX4__BFS_H_

#include "Searcher.h"
#include "Matrix.h"
#include <vector>
#include <string>
#include <queue>
#include <list>

using namespace std;

template<typename T>

class BFS : public Searcher<string, T> {
 public:
  BFS<T>() = default;

  //search if the current cell was visited and return true, else false
  bool wasVisited(State<T> *current, list<State<T>*> visited) {
    auto iter = visited.begin();
    for (iter; iter != visited.end(); iter++) {
      State<T> *cell = *iter;
      if (current->isEqual(cell)) {
        return true;
      }
    }
    return false;
  }


  //return the direction for the best path
  string findPath(list<State<T>*> visited, State<T> *dest) {
    vector<State<T>> pathVector;
    //insert the destination cell to the path vector
    pathVector.push_back(*dest);
    State<T> *prev = dest->getPrev();

    //find the path by the previous node of each vertex
    while (prev != nullptr) {
      pathVector.push_back(*prev);
      *prev = *prev->getPrev();
    }
    //initialize the solution to be empty
    string path = "";

    State<T> current = *pathVector.end();
    int row = current.getValue()->getRowPos();
    int col = current.getValue()->getColPos();

    //iterator
    auto it = pathVector.end() - 1;

    //finds the direction for the path
    for (it; it != pathVector.begin(); it--) {
      State<T> next = *it;
      while (row < next.getValue()->getRowPos()) {
        if (current.getValue()->getRowPos() == next.getValue()->getRowPos()) {
          break;
        }
        path += "Down, ";
        row += 1;
      }
      while (row > next.getValue()->getRowPos()) {
        if (current.getValue()->getRowPos() == next.getValue()->getRowPos()) {
          break;
        }
        path += "Up, ";
        row -= 1;
      }
      while (col < next.getValue()->getColPos()) {
        if (current.getValue()->getColPos() == next.getValue()->getColPos()) {
          break;
        }
        path += "Right, ";
        col += 1;
      }
      while (col > next.getValue()->getColPos()) {
        if (current.getValue()->getColPos() == next.getValue()->getColPos()) {
          break;
        }
        path += "Left, ";
        col -= 1;
      }

      current = *it;
      row = current.getValue()->getRowPos();
      col = current.getValue()->getColPos();
    }

    //erase the space and "," in the end og the path
    path.erase(path.end() - 2, path.end());
    if (path == "") {
      throw;
    }
    return path;
  }


  //search the given problem
  string search(Searchable<T> *searchable) {
    queue<State<T>*> q;
    list<State<T>*> visited;
    State<T> *current;
    int verticesCounter = 0;

    //get the initial cell
    q.push(searchable->getInitialState());
    //insert the start point to the visited list
    //visited.push_back(searchable->getInitialState());

    while (!q.empty()) {
      current = q.front();
      q.pop();
      if (wasVisited(current, visited)) {
        continue;
      }
      //if it is a new cell mark it as visited cell and add to count
      visited.push_back(current);
      verticesCounter += 1;
      //initial the distance to from the beginning cell
      current->setDistance(verticesCounter);
      //if we get to the goal state done, else continue
      if (searchable->isGoalState(current)) {
        break;
      }
      //get all neighbors of the current cell
      vector<State<T> *> neighbors = searchable->getAllPossibleStates(current);
      //for each child in expand node
      auto iter = neighbors.begin();
      for (iter; iter != neighbors.end(); iter++) {
        q.push(*iter);
      }
    }
    //find the directions of the path
    try {
      string path = findPath(visited, current);
      cout << verticesCounter << endl;
    } catch (const char *e) {
      return "Path didn't found";
    }
  }
};

#endif //EX4__BFS_H_