//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_SERVERSIDE_H
#define EX4_SERVERSIDE_H

/**
 * ServerSide Interface
 *
 * */
#include "ClientHandler.h"

namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *c) = 0;

        virtual void stop() = 0;
    };
}

#endif //EX4_SERVERSIDE_H
