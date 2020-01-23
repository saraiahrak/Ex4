//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Searcher.h"
#include <queue>
#include "AStarComparator.h"

using namespace std;

template<typename T>

class AStar : public Searcher<string, T> {
public:

    priority_queue<State<T> *, vector<State<T> *>, AStarComparator<T>> open;
    vector<State<T> *> closed;

    AStar<T> *clone() {
        return new AStar<T>();
    }

    bool isVisited(State<T> *s) {
        for (State<T> *node : closed) {
            if (node->isEqual(s)) {
                return true;
            }
        }
        return false;
    }

    void removeFromClosed(State<T> *s) {
        auto it = closed.begin();
        for (it; it != closed.end(); it++) {
            if (s->isEqual(*it)) {
                break;
            }
        }
        if (it != closed.end()) {
            closed.erase(it);
        }
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

    int h(State<T> *s, State<T> *goal) {
        int dx = goal->getValue()->getColPos() - s->getValue()->getColPos();
        int dy = goal->getValue()->getRowPos() - s->getValue()->getRowPos();
        return dx + dy;
    }


    string search(Searchable<T> *searchable) {
        State<T> *current;
        initialize(searchable);
        vector<State<T> *> neighbors;
        int value;
        int trail;
        while (!open.empty()) {
            current = open.top();
            open.pop();
            closed.push_back(current);


            if (searchable->isGoalState(current)) {
                return constructPath(current);
            }

            neighbors = searchable->getAllPossibleStates(current);

            for (State<T> *neighbor : neighbors) {
                neighbor->setCost(neighbor->getValue()->getValue());
                trail = current->getTrailCost() + neighbor->getCost();
                if (isInOpen(neighbor)) {
                    if (current->getTrailCost() <= trail) {
                        continue;
                    }
                } else if (isVisited(neighbor)) {
                    if (current->getTrailCost() <= trail) {
                        continue;
                    }
                    neighbor->setTrailCost(trail);
                    neighbor->setPrev(current);
                    open.push(neighbor);
                    removeFromClosed(neighbor);
                } else {
                    neighbor->setTrailCost(trail);
                    neighbor->setPrev(current);
                    open.push(neighbor);
                }

            }
        }

    }

    ~AStar() = default;
};

#endif //EX4_ASTAR_H
