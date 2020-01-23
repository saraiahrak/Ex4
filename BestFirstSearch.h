//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H

#include "State.h"
#include "Searcher.h"
#include "StateComparator.h"
#include <string>
#include <list>
#include <queue>


using namespace std;

template<typename T>
class BestFirstSearch : public Searcher<string, T> {
public:
    priority_queue<State<T> *, vector<State<T> *>, StateComparator<T>> open;
    vector<State<T> *> visited;

    bool isVisited(State<T> *s) {
        for (State<T> *node : visited) {
            if (node->isEqual(s)) {
                return true;
            }
        }
        return false;
    }

    bool isInOpen(State<T> *s) {
        vector<State<T> *> storage;
        int index = 0;

        while (!open.empty()) {
            auto *temp = open.top();
            storage.push_back(temp);
            if (s->isEqual(temp)) {
                while (index < storage.size()) {
                    open.push(storage.at(index));
                    index++;
                }
                storage.clear();
                return true;
            }
            open.pop();
        }
        while (index < storage.size()) {
            open.push(storage.at(index));
            index++;
        }
        return false;
    }

    void initialize(Searchable<T> *s) {
        State<T> *first = s->getInitialState();
        first->setCost(first->getValue()->getValue());
        first->setTrailCost(first->getValue()->getValue());
        open.push(first);
    }

    string getDirection(State<T> *current, State<T> *prev) {

        string direction;

        int currentRow = current->getValue()->getRowPos();
        int currentCol = current->getValue()->getColPos();
        int prevRow = prev->getValue()->getRowPos();
        int prevCol = prev->getValue()->getColPos();

        if (prevRow < currentRow) {
            direction += "Down (";
        }
        if (prevRow > currentRow) {
            direction += "Up (";
        }
        if (prevCol < currentCol) {
            direction += "Right (";
        }
        if (prevCol > currentCol) {
            direction += "Left (";
        }

        return direction;

    }

    string constructPath(State<T> *goal) {
        string path;

        State<T> *current = goal;

        while (current->getPrev()) {
            State<T> *prev = current->getPrev();
            path.insert(0, ")");
            path.insert(0, to_string(current->getTrailCost()));
            path.insert(0, getDirection(current, prev));
            current = prev;

            if (current->getPrev() != NULL) {
                path.insert(0, ", ");
            }
        }
        path += "\r\n";
        return path;
    }


    string search(Searchable<T> *searchable) {
        State<T> *current;
        initialize(searchable);
        vector<State<T> *> neighbors;
        int trail;
        while (!open.empty()) {
            current = open.top();
            visited.push_back(current);
            open.pop();

            if (searchable->isGoalState(current)) {
                return constructPath(current);
            }

            neighbors = searchable->getAllPossibleStates(current);

            for (State<T> *neighbor : neighbors) {
                if (isVisited(neighbor)) {
                    continue;
                }
                neighbor->setCost(neighbor->getValue()->getValue());
                trail = current->getTrailCost() + neighbor->getCost();
                if (!isInOpen(neighbor) && !isVisited(neighbor)) {
                    neighbor->setPrev(current);
                    neighbor->setTrailCost(trail);
                    open.push(neighbor);
                } else {
                    if (trail < neighbor->getTrailCost()) {
                        neighbor->setTrailCost(trail);
                        neighbor->setPrev(current);
                    }
                }
            }

        }
    }

    ~BestFirstSearch() = default;
};

#endif //EX4_BESTFIRSTSEARCH_H
