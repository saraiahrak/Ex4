
//
// Created by dekel on 14/01/2020.
//

#include "MyClientHandler.h"
#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>

using namespace std;


MyClientHandler::MyClientHandler(CacheManager *cm, Solver<string, string> *s) {
  this->cacheManager = cm;
  this->solver = s;
}

//reads the information sent from the server
void MyClientHandler::handleClient(int clientSocket) {
  vector<string> problem;
  string current;
  string solution;
  bool endFlag = false;
  while (!MySerialServer::isStop) {
    //if values is not empty in the beggining of the iteration- clear to receive new values
    if (!problem.empty()) {
      problem.clear();
      current = "";
      solution = "";
    }

    char buffer[1];
    int valread = read(clientSocket, buffer, 1);
    if (valread < 0) {
      continue;
    }

    //reads information that ends with new line, each value seperated by comma
    while (buffer[0] != '\n') {
      current += buffer[0];
      valread = read(clientSocket, buffer, 1);
    }
    //insert last value
    if (!current.empty()) {
      problem.push_back(current);
    }
    //end the communication when received "end"
    if (current == "end\r") {
      endFlag = true;
      //search or solve the solution
      try {
        solution = cacheManager->getSolution(problem);
      } catch (const char *e) {
        //solve the new problem
        solution = solver->solve(problem);
        //insert the new problem and his solution to the cache manager
        cacheManager->insert(problem, solution);
      }
    }
    //sending the solution to the client
    int is_sent = write(clientSocket, solution.c_str(), solution.length());
    while (is_sent == -1) {
      //Error sending message- trying again
      cout << "Error sending message" << endl;
      is_sent = write(clientSocket, solution.c_str(), solution.length());
    }
    if (endFlag) {
      break;
    }
  }
}
