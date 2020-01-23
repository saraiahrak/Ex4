
//
// Created by dekel on 14/01/2020.
//

#include "MyClientHandler.h"
#include "MySerialServer.h"
#include "Utils.h"
#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;

MyClientHandler::MyClientHandler(CacheManager *cm, Solver<string, string> *s) {
    this->cacheManager = cm;
    this->solver = s;
}

//reads the information sent from the server
void MyClientHandler::handleClient(int clientSocket) {
    string problem;
    string current;
    string solution;
    bool endFlag = false;

    while (!MySerialServer::isStop) {
        //reads information that ends with new line and separate it into vector of strings
        while (!endFlag) {
            //clear
            current.clear();
            solution.clear();
            //initial buffer
            char buffer[1] = {0};
            int valread = read(clientSocket, buffer, 1);
            if (valread < 0) {
                continue;
            }

            while (buffer[0] != '\n') {
                current += buffer[0];
                valread = read(clientSocket, buffer, 1);
            }

            //end the communication when received "end"
            size_t pos = current.find("end");
            if (pos != string::npos) {
                if (problem.empty()) {
                    exit(-1);
                }

                endFlag = true;
                break;
            }
            current = Utils::strip(current);
            problem += current + "\n";
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
        if (is_sent < 0) {
            //Error sending message- trying again
            cout << "Error sending message" << endl;
            //is_sent = write(clientSocket, solution.c_str(), solution.length());
        }
        if (endFlag) {
            close(clientSocket);
            break;
        }
    }
}


