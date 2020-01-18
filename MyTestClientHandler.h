//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "MySerialServer.h"
#include "CacheManager.h"
#include "Solver.h"

class MyTestClientHandler : public ClientHandler {
public:
    CacheManager *cacheManager;
    Solver<string, string> *solver;

    MyTestClientHandler(CacheManager *c, Solver<string, string> *s);

    void handleClient(int clientSocket) override;

};

#endif //EX4_MYTESTCLIENTHANDLER_H
