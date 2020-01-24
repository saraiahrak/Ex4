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

//Best First Search algorithm
class BestFirstSearch : public Searcher<string, T> {
public:

    string id;
    priority_queue<State<T> *, vector<State<T> *>, StateComparator<T>> open;
    vector<State<T> *> visited;

    //constructor
    BestFirstSearch<T>() {
        this->id = "BestFS";
    }

    //get the name of the algorithm
    string getId() {
        return this->id;
    }

    //deep clone the algorithm
    BestFirstSearch<T> *clone() {
        return new BestFirstSearch<T>;
    }

    //check if the given state was already explored- and is in the visited vector
    bool isVisited(State<T> *s) {
        for (State<T> *node : visited) {
            if (node->isEqual(s)) {
                return true;
            }
        }
        return false;
    }

    //check if the given state is in the open queue
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

    //remove a given state from the open queue
    void removeFromOpen(State<T> *s) {
        vector<State<T> *> storage;
        int index = 0;
        bool flag = false;

        while (!open.empty()) {
            auto *temp = open.top();
            if (s->isEqual(temp)) {
                open.pop();
                while (index < storage.size()) {
                    open.push(storage.at(0));
                    storage.erase(storage.begin());
                }
                storage.clear();
                break;
            }
            storage.push_back(temp);
            open.pop();
        }
        while (index < storage.size()) {
            open.push(storage.at(index));
            index++;
        }
    }

    //initialize the search
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

    //construct the path of the algorithm from the last state going back to the first
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

    //main search algorithm
    string search(Searchable<T> *searchable) {
        State<T> *current;
        initialize(searchable);
        vector<State<T> *> neighbors;
        int trail;
        while (!open.empty()) {
            //get the top state of the open priority queue
            current = open.top();
            visited.push_back(current);
            open.pop();

            //if current is the goal state, return the path
            if (searchable->isGoalState(current)) {
                return constructPath(current);
            }

            //get the neighbor states of the current state
            neighbors = searchable->getAllPossibleStates(current);

            //iterate over the neighbors
            for (State<T> *neighbor : neighbors) {
                //if we already explored the state, continute to next neighbor
                if (isVisited(neighbor)) {
                    continue;
                }
                //set the cost and calculate the trail cost
                neighbor->setCost(neighbor->getValue()->getValue());
                trail = current->getTrailCost() + neighbor->getCost();
                //if we never encountered the state
                if (!isInOpen(neighbor) && !isVisited(neighbor)) {
                    //set the values, push to open queue
                    neighbor->setPrev(current);
                    neighbor->setTrailCost(trail);
                    open.push(neighbor);
                } else {
                    //if we found a better trail
                    if (trail <= neighbor->getTrailCost()) {
                        //set the trail to the new trail, set the prev
                        neighbor->setTrailCost(trail);
                        neighbor->setPrev(current);
                        removeFromOpen(neighbor);
                        open.push(neighbor);
                    }
                }
            }

        }
    }

    //destructor
    ~BestFirstSearch() = default;
};

#endif //EX4_BESTFIRSTSEARCH_H
