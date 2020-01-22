//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__DFS_H_
#define EX4__DFS_H_
#include "Matrix.h"
#include "Searchable.h"
#include <vector>
#include <string>
#include <stack>
#include <list>

using namespace std;

template<typename T>

class DFS : public Searcher<T, vector<State<T>*>> {
public:
    DFS();


  //search if the current cell was visited and return true, else false
  bool wasVisited(State<T> *current, list<State<T>*> visited) {
    auto iter = visited.begin();
    for (iter; iter != visited.end(); iter++) {
      State<T> *cell = *iter;
      if (current->isEqual(*cell)) {
        return true;
      }
    }
    return false;
  }


  //insert the neighbors to the queue
  stack<State<T>*> updateQueue(stack<State<T>*> s, vector<State<T*> *> neighbors) {
    auto iter = neighbors.begin();
    for (iter; iter != neighbors.end(); iter++) {
      s.push(iter);
    }
    return s;
  }


  //return the direction for the best path
  string findPath(list<State<T>*> visited, State<T> dest) {
    vector<State<Cell>*> pathVector;
    //insert the destination cell to the path vector
    pathVector.push_back(dest);
    State<T> prev = dest.getPrev();

    //find the path by the previous node of each vertex
    while (prev != nullptr) {
      pathVector.push_back(prev);
      prev = prev.getPrev();
    }
    //initialize the solution to be empty
    string path = nullptr;

    State<T> *current = pathVector.end();
    int row = current->GetCell().getRowPos();
    int col = current->GetCell().getColPos();

    //iterator
    auto it = pathVector.end() - 1;

    //finds the direction for the path
    for (it; it != pathVector.begin(); it--) {
      State<T> *next = *it;
      while (row < next->GetCell().getRowPos()) {
        if (current->GetCell().getRowPos().isEqual(next->GetCell().getRowPos())) {
          break;
        }
        path += "Down, ";
        row += 1;
      }
      while (row > next->GetCell().getRowPos()) {
        if (current->GetCell().getRowPos().isEqual(next->GetCell().getRowPos())) {
          break;
        }
        path += "Up, ";
        row -= 1;
      }
      while (col < next->GetCell().getColPos()) {
        if (current->GetCell().getColPos().isEqual(next->GetCell().getColPos())) {
          break;
        }
        path += "Right, ";
        col += 1;
      }
      while (col > next->GetCell().getColPos()) {
        if (current->GetCell().getColPos().isEqual(next->GetCell().getColPos())) {
          break;
        }
        path += "Left, ";
        col -= 1;
      }

      current = it;
      row = current->GetCell().getRowPos();
      col = current->GetCell().getColPos();
    }

    //erase the space and "," in the end og the path
    path.erase(path.end() - 2, path.end());
    return path;
  }


  //search the given problem
  string search(Searchable<T> *searchable) {
    stack<State<T>*> s;
    list<State<T>*> visited;
    State<T> current;
    int verticesCounter = 0;

    //get the initial cell
    s.push(searchable->getInitialState());
    //insert the start point to the visited list
    visited.push_back(searchable->getInitialState());

    while (!s.empty()) {
      current = s.top();
      s.pop();
      if (wasVisited(current, visited)) {
        continue;
      }
      //if it is a new cell mark it as visited cell and add to count
      visited.push_back(current);
      verticesCounter += 1;
      //initial the distance to from the beginning cell
      current.setDistance(verticesCounter);
      //if we get to the goal state done, else continue
      if (searchable->isGoalState(current)) {
        break;
      }
      //get all neighbors of the current cell
      vector<State<T*> *> neighbors = searchable->getAllPossibleStates(current);
      //for each child in expand node
      s = updateQueue(s, neighbors);
    }
    //find the directions of the path
    try {
      string path = findPath(visited, current);
    } catch (const char *e) {
      return "Path didn't found";
    }
  }

};

#endif //EX4__DFS_H_