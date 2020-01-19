//
// Created by dekel on 15/01/2020.
//

#include "MyTestClientHandler.h"
#include <vector>

using namespace std;

MyTestClientHandler::MyTestClientHandler(CacheManager *cm, Solver<string, string> *s) {
  this->cacheManager = cm;
  this->solver = s;
}

//reads the information sent from the server
void MyTestClientHandler::handleClient(int clientSocket) {
  vector<string> problem;
  string current;
  string solution;
  while (!MySerialServer::isStop) {
    //if values is not empty in the beginning of the iteration- clear to receive new values
    if (!problem.empty()) {
      problem.clear();
      current.clear();
      solution.clear();
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
      close(clientSocket);
      break;
    }
    //search or solve the solution
    try {
      solution = cacheManager->getSolution(current);
    } catch (const char *e) {
      //solve the new problem
      solution = solver->solve(current);
      //insert the new problem and his solution to the cache manager
      cacheManager->insert(current, solution);
    }

    //sending the solution to the client
    int is_sent = write(clientSocket, solution.c_str(), solution.length());
    while (is_sent == -1) {
      //Error sending message- trying again
      cout << "Error sending message" << endl;
      is_sent = write(clientSocket, solution.c_str(), solution.length());
    }
  }
}
