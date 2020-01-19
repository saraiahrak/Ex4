//
// Created by dekel on 15/01/2020.
//

#ifndef EX4__MYCLIENTHANDLER_H_
#define EX4__MYCLIENTHANDLER_H_

#include "ClientHandler.h"

class MyClientHandler : public ClientHandler {
public:
    void handleClient(int clientSocket);
};


#endif //EX4__MYCLIENTHANDLER_H_
