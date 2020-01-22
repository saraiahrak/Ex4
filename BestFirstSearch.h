//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H

#include <queue>
#include <list>
#include "State.h"
#include "Searcher.h"
#include <string>
#include "StateComparator.h"


using namespace std;

template<typename T>
class BestFirstSearch : public Searcher<string, T> {
public:
    string solution;
    priority_queue<State<T> *, vector<State<T> *>, StateComparator<T>> open;
    list<State<T> *> visited;

    bool isVisited(State<T>* s) {
        return visited.find(s) != visited.end();
    }

    bool isInOpen(State<T>* s) {
        list<State<T>*> storage;
        int index = 0;

        while(!open.empty()){
            auto * temp = open.top();
            if (s->isEqual(temp)) {
                while(index < storage.size()) {
                    open.push(storage.at(index));
                    index++;
                }
                storage.clear();
                return true;
            }
        }
        return false;
    }

    void initialize(Searchable<T> * s) {
        State<T>* first = s->getInitialState();
        first->setCost(first->getValue()->getValue());
        open.push(first);
    }

    string constructPath(State<T>* s) {

    }


    string search(Searchable<T> * searchable) {
        State<T>* current;
        initialize(searchable);
        vector<State<T>*> neighbors;
        while(!open.empty()) {
            current = open.top();
            visited.push(current);
            open.pop();

            if (searchable->isGoalState(current)) {
                return constructPath(current);
            }

            neighbors = searchable->getAllPossibleStates(current);

            for(State<T>* neighbor : neighbors) {
                if (!isVisited(neighbor) && !isInOpen(neighbor)) {
                    neighbor->setCost(neighbor->getValue()->getValue());
                    neighbor->setPrev(current);
                    neighbor->setTrailCost(current->getTrailCost() + neighbor->getCost());
                    open.push(neighbor);
                } else {

                }
            }

        }
    }

};

#endif //EX4_BESTFIRSTSEARCH_H
