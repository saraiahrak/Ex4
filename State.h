//
// Created by sarai on 20/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H


template<class T>

class State {
public:
    explicit State<T>(T st) {
        this->value = st;
        this->trailCost = 0;
        this->cost = 0;
        this->heuristic = 0;
        this->distance = 0;
        this->prev = nullptr;
    }

    ~State() = default;

    void setCost(int c) {
        this->cost = c;
    }

    void setTrailCost(int tc) {
        this->trailCost = tc;
    }

    void setPrev(State<T> *s) {
        this->prev = s;
    }

    int getHeuristic() {
        return this->heuristic;
    }

    int getDistance() {
        return this->distance;
    }

    void setHeuristic(int heur) {
        this->heuristic = heur;
    }

    void setDistance(int x) {
        this->distance = x;
    }

    State<T> *getPrev() {
        return this->prev;
    }

    bool isEqual(State<T> *s) {
        return value->isEqual(s->value);
    }

    T getValue() {
        return this->value;
    }

    int getCost() {
        return this->cost;
    }

    int getTrailCost() {
        return this->trailCost;
    }

private:

    int cost;

    int trailCost;

    int heuristic;

    int distance;

    State<T> *prev;

    T value;

};

#endif //EX4_STATE_H
