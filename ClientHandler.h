//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H
using namespace std;

#include <iostream>

class ClientHandler {
public:
    virtual void handleClient(int socket) = 0;

    virtual ClientHandler* clone() = 0;

    virtual ~ClientHandler() = default;
};

#endif //EX4_CLIENTHANDLER_H
