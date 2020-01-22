////
//// Created by dekel on 18/01/2020.
////
//
//#include "DFS.h"
//#include <string>
//#include <vector>
//#include <stack>
//#include <list>
//
//using namespace std;
//
////create an algorithm for traversing or searching tree or graph data structures
//DFS::DFS() {}
//
//
////trace the path from the source to destination
//string DFS::findPath(vector<vector<pair<int, int>>> graph, pair<int, int> dest) {
//    int row, col, fatherRow, fatherCol;
//    row = dest.first;
//    col = dest.second;
//
//    //find all the paths in the graph
//    list<pair<int, int>> pathList;
//    while (!(graph[row][col].first == row && graph[row][col].second == col)) {
//        pathList.push_front(make_pair(row, col));
//        int tempRow = graph[row][col].first;
//        int tempCol = graph[row][col].second;
//        row = tempRow;
//        col = tempCol;
//    }
//    pathList.push_front(make_pair(row, col));
//
//    //initialize the solution to be empty
//    string path = "";
//
//    fatherRow = pathList.front().first;
//    fatherCol = pathList.front().second;
//
//    //iterator
//    list<pair<int, int>>::iterator it;
//
//    for (it = (pathList.begin()++); it != pathList.end(); ++it) {
//        row = it->first;
//        col = it->second;
//
//        if (row < fatherRow) {
//            path += "Up, ";
//        } else if (row > fatherRow) {
//            path += "Down, ";
//        } else if (col < fatherCol) {
//            path += "Left, ";
//        } else if (col > fatherCol) {
//            path += "Right, ";
//        }
//
//        fatherRow = it->first;
//        fatherCol = it->second;
//    }
//
//    //erase the destination
//    path.erase(path.end() - 2, path.end());
//    return path;
//}
//
//
////finds the parent links trace the shortest path back to root
//string DFS::search(Matrix *m, pair<int, int> source, pair<int, int> destination) {
//    vector<vector<int>> matrix = m->getMatrix();
//    int rows, cols;
//    rows = m->getCell().first;
//    cols = m->getCell().second;
//
//    //boolean that checks if the point was visited before
//    bool visited[rows][cols];
//
//    //initialize all the points to be unvisited
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            visited[i][j] = false;
//        }
//    }
//
//    //save the parent of each vertex
//    vector<vector<pair<int, int>>> parents;
//    for (int i = 0; i < rows; i++) {
//        vector<pair<int, int>> vertex = {};
//        for (int j = 0; j < cols; j++) {
//            vertex.push_back({-1, -1});
//        }
//        parents.push_back(vertex);
//    }
//
//    //initialize the source
//    parents[source.first][source.second] = {source.first, source.second};
//    Matrix::CurrentNode src = {source.first, source.second, 0};
//
//    //DFS algorithm
//    stack<Matrix::CurrentNode> s;
//    s.push(src);
//
//    //mark that visited
//    visited[src.row][src.column] = true;
//
//    //while the stack isn't empty
//    while (!s.empty()) {
//      Matrix::CurrentNode p = s.top();
//
//        //if p equal to the destination point
//        if (p.row == destination.first && p.column == destination.second) {
//            //return the path
//            return findPath(parents, destination);
//        }
//
//        int rowDirection[] = {0, 1, 0, -1};
//        int colDirection[] = {1, 0, -1, 0};
//
//        bool allVisited = true;
//
//        for (int k = 0; k < 4; k++) {
//            int i = p.row + rowDirection[k];
//            int j = p.column + colDirection[k];
//            if (m->isInRange(i, j) && m->isUnBlocked(i, j) && !visited[i][j]) {
//                s.push({i, j, p.dist + matrix[i][j]});
//                visited[i][j] = true;
//                parents[i][j] = {p.row, p.column};
//
//                allVisited = false;
//                break;
//            }
//        }
//        if (allVisited) {
//            s.pop();
//        }
//    }
//    return "Path didn't found";
//}
