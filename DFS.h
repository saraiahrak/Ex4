//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__DFS_H_
#define EX4__DFS_H_

#include "Matrix.h"
#include "Searcher.h"
#include <vector>
#include <string>
#include <stack>
#include <list>

using namespace std;

template<typename T>

class DFS : public Searcher<string, T> {
public:

    string id;

    DFS<T>() {
        this->id = "DFS";
    }

    string getId() {
        return this->id;
    }

    DFS<T> *clone() {
        return new DFS<T>();
    }


    //search if the current cell was visited and return true, else false
    bool wasVisited(State<T> *current, list<State<T> *> visited) {
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
    string findPath(list<State<T> *> visited, State<T> *dest, Searchable<T> *searchable) {
        vector<State<T>> pathVector;
        //insert the destination cell to the path vector
        pathVector.push_back(*dest);

        //find the path by the previous node of each vertex
        State<T> *prev = dest->getPrev();
        while (!prev->isEqual(searchable->getInitialState())) {
            pathVector.push_back(*prev);
            *prev = *prev->getPrev();
        }
        pathVector.push_back(*prev);

        //initialize the solution to be empty
        string path = "";

        State<T> current = pathVector.at(pathVector.size() - 1);
        int row = current.getValue()->getRowPos();
        int col = current.getValue()->getColPos();

        int trailCost = prev->getCost();
        int i;
        //finds the direction for the path
        for (i = pathVector.size() - 2; i >= 0; i--) {
            State<T> next = pathVector.at(i);
            if (row < next.getValue()->getRowPos()) {
                //string cost = current.getValue();
                path += "Down (" + to_string(next.getCost() + trailCost) + "), ";
                trailCost += next.getCost();
            }
            if (row > next.getValue()->getRowPos()) {
                path += "Up (" + to_string(next.getCost() + trailCost) + "), ";
                trailCost += next.getCost();
            }
            if (col < next.getValue()->getColPos()) {
                path += "Right (" + to_string(next.getCost() + trailCost) + "), ";
                trailCost += next.getCost();
            }
            if (col > next.getValue()->getColPos()) {
                path += "Left (" + to_string(next.getCost() + trailCost) + "), ";
                trailCost += next.getCost();
            }

            current = next;
            row = current.getValue()->getRowPos();
            col = current.getValue()->getColPos();
        }

        //erase the space and "," in the end og the path
        path.erase(path.end() - 2, path.end());
        path += "\r\n";
        if (path == "") {
            throw;
        }
        cout << "trailCost: " + to_string(trailCost) << endl;
        return path;
    }


    //search the given problem
    string search(Searchable<T> *searchable) {
        stack<State<T> *> s;
        list<State<T> *> visited;
        State<T> *current;
        int verticesCounter = 0;

        //get the initial cell
        s.push(searchable->getInitialState());

        while (!s.empty()) {
            current = s.top();
            current->setCost(current->getValue()->getValue());
            s.pop();
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
            for (State<T> *neighbor : neighbors) {
                if (!wasVisited(neighbor, visited)) {
                    neighbor->setPrev(current);
                }
                s.push(neighbor);
            }
        }
        //find the directions of the path
        try {
            string path = findPath(visited, current, searchable);
            cout << "number of vertices: " + to_string(verticesCounter) << endl;
            return path;
        } catch (const char *e) {
            return "Path didn't found";
        }
    }

  ~DFS() = default;
};

#endif //EX4__DFS_H_