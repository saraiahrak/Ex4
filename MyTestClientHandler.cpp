//
// Created by dekel on 15/01/2020.
//

#include "MyTestClientHandler.h"

using namespace std;

MyTestClientHandler::MyTestClientHandler(CacheManager *cm, Solver<string, string> *s) {
  this->cacheManager = cm;
  this->solver = s;
}

//reads the information sent from the server
void MyTestClientHandler::handleClient(int clientSocket) {
  string problem;
  string solution;
  while (!MySerialServer::isStop) {

    char buffer[1] = {0};
    int valread = read(clientSocket, buffer, 1);
    if (valread < 0) {
      continue;
    }
    //reads information that ends with new line, each value seperated by comma
    while (buffer[0] != '\n') {
      problem += buffer[0];
      valread = read(clientSocket, buffer, 1);
    }
    //end the communication when received "end"
    if (problem == "end\r") {
      close(clientSocket);
      break;
    }
    //search or solve the solution
    try {
      solution = cacheManager->getSolution(problem);
    } catch (const char *e) {
      //solve the new problem
      solution = solver->solve(problem);
      //insert the new problem and his solution to the cache manager
      cacheManager->insert(problem, solution);
    }

    //sending the solution to the client
    int is_sent = write(clientSocket, solution.c_str(), solution.length());
    while (is_sent < 0) {
      //Error sending message- trying again
      cout << "Error sending message" << endl;
      is_sent = write(clientSocket, solution.c_str(), solution.length());
    }
    solution.clear();
    problem.clear();
  }
}
