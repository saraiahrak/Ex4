//
// Created by dekel on 18/01/2020.
//

#include "BFS.h"
#include <string>
#include <vector>
#include <queue>
#include <list>

using namespace std;

//create an algorithm for traversing or searching tree or graph data structures
BFS::BFS() {}

//trace the path from the source to destination
string BFS::findPath(vector<vector<pair<int, int>>> graph, pair<int, int> dest) {
    int row, col, fatherRow, fatherCol, vertexCounter = 0;
    row = dest.first;
    col = dest.second;

    //find all the paths in the graph
    list<pair<int, int>> pathList;

    while (!(graph[row][col].first == row && graph[row][col].second == col)) {
        pathList.push_front(make_pair(row, col));
        int tempRow = graph[row][col].first;
        int tempCol = graph[row][col].second;
        row = tempRow;
        col = tempCol;
    }
    pathList.push_front(make_pair(row, col));

    //initialize the solution to be empty
    string path = "";

    fatherRow = pathList.front().first;
    fatherCol = pathList.front().second;

    //iterator
    list<pair<int, int>>::iterator it;

    for (it = (pathList.begin()++); it != pathList.end(); ++it) {
        row = it->first;
        col = it->second;

        if (row < fatherRow) {
            path += "Up, ";
        } else if (row > fatherRow) {
            path += "Down, ";
        } else if (col < fatherCol) {
            path += "Left, ";
        } else if (col > fatherCol) {
            path += "Right, ";
        }

        //count the vertex that were visited
        vertexCounter += 1;

        fatherRow = it->first;
        fatherCol = it->second;
    }

    //erase the space and "," in the end og the path
    path.erase(path.end() - 2, path.end());
    return path;
}


//finds the parent links trace the shortest path back to root
string BFS::search(Searchable<Matrix> *state) {


  //string search(Matrix *m, pair<int, int> source, pair<int, int> destination);
    int rows, cols, destRow, destCol;
    //get the size of the matrix
    rows = state.getInitialState()->getStateStruct().getStateStruct()->getRowNum();
    cols = state.getInitialState()->getStateStruct().getStateStruct()->getColNum();
    //get the destination
    destRow = state.


    //boolean that checks if the point was visited before
    bool visited[rows][cols];

    //initialize all the points to be unvisited
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
        }
    }

    //save the parent of each vertex
    vector<vector<pair<int, int>>> parents;
    for (int i = 0; i < rows; i++) {
        vector<pair<int, int>> vertex = {};
        for (int j = 0; j < cols; j++) {
            vertex.push_back({-1, -1});
        }
        parents.push_back(vertex);
    }

    //initialize the source
    parents[source.first][source.second] = {source.first, source.second};
    Matrix::CurrentNode src = {source.first, source.second, 0};

    //BFS algorithm
    queue<Matrix::CurrentNode> q;
    q.push(src);
    //mark that visited
    visited[src.row][src.column] = true;

    //while the queue isn't empty
    while (!q.empty()) {
        Matrix::CurrentNode p = q.front();
        q.pop();

        //if p equal to the destination point
        if (p.row == destination.first && p.column == destination.second) {
            //return the path
            return findPath(parents, destination);
        }

        int rowDirection[] = {0, 1, 0, -1};
        int colDirection[] = {1, 0, -1, 0};

        for (int k = 0; k < 4; k++) {
            int i = p.row + rowDirection[k];
            int j = p.column + colDirection[k];
            if (m->isInRange(i, j) && m->isUnBlocked(i, j) && !visited[i][j]) {
                q.push({i, j, p.dist + matrix[i][j]});
                visited[i][j] = true;
                parents[i][j] = {p.row, p.column};
            }
        }
    }
    return "Path didn't found";
}

