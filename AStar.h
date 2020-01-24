//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Searcher.h"
#include "AStarComparator.h"
#include <queue>

using namespace std;

template<typename T>

//AStar Algorithm
class AStar : public Searcher<string, T> {
public:

    string id;

    //priority queue- puts the stated in order determined by the AStar Comparator
    priority_queue<State<T> *, vector<State<T> *>, AStarComparator<T>> open;
    vector<State<T> *> closed;

    //constructor
    AStar<T>() {
        this->id = "AStar";
    }

    //get name of algorithm
    string getId() {
        return this->id;
    }

    //deep clone the algorithm
    AStar<T> *clone() {
        return new AStar<T>();
    }

    //check if the given state was already explored and put in closed
    bool isVisited(State<T> *s) {
        for (State<T> *node : closed) {
            if (node->isEqual(s)) {
                return true;
            }
        }
        return false;
    }

    //remove a given state from the closed vector
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

    //check if a given state is in the open queue
    bool isInOpen(State<T> *s) {
        vector<State<T> *> storage;
        int index = 0;

        while (!open.empty()) {
            auto *temp = open.top();
            if (s->isEqual(temp)) {
                while (index < storage.size()) {
                    open.push(storage.at(index));
                    index++;
                }
                storage.clear();
                return true;
            }
            storage.push_back(temp);
            open.pop();
        }
        while (index < storage.size()) {
            open.push(storage.at(index));
            index++;
        }
        return false;
    }

    //initialize the search with the first state
    void initialize(Searchable<T> *s) {
        State<T> *first = s->getInitialState();
        first->setCost(first->getValue()->getValue());
        first->setTrailCost(first->getValue()->getValue());

        open.push(first);
    }

    //get the direction of movement in the algorithm given a current and it's previous state
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

    //Build the path from the last state going back to the first using the prevs
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

    //calculate the heuristic value used by AStar
    int h(State<T> *s, State<T> *goal) {
        int dx = goal->getValue()->getColPos() - s->getValue()->getColPos();
        int dy = goal->getValue()->getRowPos() - s->getValue()->getRowPos();
        return dx + dy;
    }


    //Main search algorithm
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

            //if we reached the goal state, return the path string
            if (searchable->isGoalState(current)) {
                return constructPath(current);
            }

            //get the neighbor states of the current state
            neighbors = searchable->getAllPossibleStates(current);

            //iterate over each neighbor
            for (State<T> *neighbor : neighbors) {

                //set cost and calculate trail
                neighbor->setCost(neighbor->getValue()->getValue());
                trail = current->getTrailCost() + neighbor->getCost();

                //if the neighbor is already added to the open list
                if (isInOpen(neighbor)) {

                    //if we didn't find a better path- continue to next neighbor
                    if (current->getTrailCost() <= trail) {
                        continue;
                    }

                    //if we already explored the neighbor
                } else if (isVisited(neighbor)) {
                    //if we didn't find a better path- continue to next neighbor
                    if (current->getTrailCost() <= trail) {
                        continue;
                    }
                    //otherwise- move from closed to open and set values to the optimal path
                    neighbor->setTrailCost(trail);
                    neighbor->setPrev(current);
                    open.push(neighbor);
                    removeFromClosed(neighbor);
                    //if it's a state we never explored
                } else {
                    //set all relevent values
                    neighbor->setTrailCost(trail);
                    neighbor->setPrev(current);
                    open.push(neighbor);
                }

                neighbor->setTrailCost(trail);
                neighbor->setPrev(current);

            }
        }

    }

    //destructor
    ~AStar() = default;
};

#endif //EX4_ASTAR_H
