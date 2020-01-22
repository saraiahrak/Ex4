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

        int i;
        int trailCost = 0;
        //finds the direction for the path
        for (i = pathVector.size() - 2; i >= 0; i--) {
            State<T> next = pathVector.at(i);
            while (row < next.getValue()->getRowPos()) {
                if (current.getValue()->getRowPos() == next.getValue()->getRowPos()) {
                    break;
                }
                //string cost = current.getValue();
                path += "Down (" + to_string(current.getCost() + trailCost) + "), ";
                trailCost += current.getCost();
                row += 1;
            }
            while (row > next.getValue()->getRowPos()) {
                if (current.getValue()->getRowPos() == next.getValue()->getRowPos()) {
                    break;
                }
                path += "Up (" + to_string(current.getCost() + trailCost) + "), ";
                trailCost += current.getCost();
                row -= 1;
            }
            while (col < next.getValue()->getColPos()) {
                if (current.getValue()->getColPos() == next.getValue()->getColPos()) {
                    break;
                }
                path += "Right (" + to_string(current.getCost() + trailCost) + "), ";
                trailCost += current.getCost();
                col += 1;
            }
            while (col > next.getValue()->getColPos()) {
                if (current.getValue()->getColPos() == next.getValue()->getColPos()) {
                    break;
                }
                path += "Left (" + to_string(current.getCost() + trailCost) + "), ";
                trailCost += current.getCost();
                col -= 1;
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
        return path;
    }


    //search the given problem
    string search(Searchable<T> *searchable) {
        queue<State<T> *> q;
        list<State<T> *> visited;
        State<T> *current;
        int verticesCounter = 0;

        //get the initial cell
        q.push(searchable->getInitialState());
        //insert the start point to the visited list

        while (!q.empty()) {
            current = q.front();
            current->setCost(current->getValue()->getValue());
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
            for (State<T> *neighbor : neighbors) {
                if (!wasVisited(neighbor, visited)) {
                    neighbor->setPrev(current);
                }
                q.push(neighbor);
            }
        }
        //find the directions of the path
        try {
            string path = findPath(visited, current, searchable);
            cout << verticesCounter << endl;
            return path;
        } catch (const char *e) {
            return "Path didn't found";
        }
    }
};

#endif //EX4__BFS_H_