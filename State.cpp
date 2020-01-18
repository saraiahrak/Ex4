////
//// Created by dekel on 18/01/2020.
////
//
//#include "State.h"
//
//struct State::CurrentNode;
//
////constructor for the matrix graph
//State::State(vector<vector<int>> matrix) {
//    this->matrix = matrix;
//    this->row = matrix.size();
//    this->column = matrix[0].size();
//}
//
//
////checks if the point is in the matrix range and returns true if in range, otherwise false
//bool State::isValid(int r, int c) {
//    return (r >= 0) && (r < this->row) && (c >= 0) && (c < this->column);
//}
//
//
////checks if the point is unblocked and returns true if unblocked, otherwise false
//bool State::isUnBlocked(int r, int c) {
//    return (matrix[r][c] != -1);
//}
//
//
////returns all the possible states
//vector<vector<int>> State::getAllPossibleStates() {
//    return this->matrix;
//}
//
//
////returns the state
//pair<int, int> State::getInitialState() {
//    return {this->row, this->column};
//}
