//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "MySerialServer.h"

class MyTestClientHandler : public ClientHandler {
public:
    CacheManager *cacheManager;
    Solver<string, string> *solver;

    MyTestClientHandler *clone() {
        return new MyTestClientHandler(this->cacheManager, this->solver->clone());
    }

    MyTestClientHandler(CacheManager *c, Solver<string, string> *s);

    ~MyTestClientHandler() = default;

    void handleClient(int clientSocket) override;

};

#endif //EX4_MYTESTCLIENTHANDLER_H
