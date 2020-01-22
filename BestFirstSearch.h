//
// Created by sarai on 21/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H

#include <queue>
#include <list>
#include "State.h"
#include "Searcher.h"
#include "StateComparator.h"


using namespace std;

template<typename T>
class BestFirstSearch : public Searcher<string, T> {
public:
    string solution;
    priority_queue<State<T> *, vector<State<T> *>, StateComparator<T>> pq;
    list<State<T> *> visited;

    bool isVisited(State<T>* s) {
        return visited.find(s) != visited.end();
    }

    string search(Searchable<T> *searchable) {
        State<T> *current = searchable->getInitialState();
        current->setCost(current->getValue()->getValue());
        pq.push(current);

        while (!pq.empty()) {
            current = pq.top();
            pq.pop();

            if (searchable->isGoalState(current)) {
                return solution;
            }

            vector<State<T> *> neighbors = searchable->getAllPossibleStates(current);

            for (State<T> *neighbor: neighbors) {
                if(!isVisited(neighbor)) {
                    visited.push_back(neighbor);
                }
            }
        }
    }


};

#endif //EX4_BESTFIRSTSEARCH_H
