//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__BOOT_H_
#define EX4__BOOT_H_

#include "MySerialServer.h"
#include "MyParallelServer.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"
#include "ObjectAdapter.h"
#include "Solver.h"
#include "BestFirstSearch.h"
#include "AStar.h"
#include "BFS.h"
#include "DFS.h"

namespace boot {
    class Main {
    public:
        Main() {}

        void main(int port) {

            server_side::Server *server = new MyParallelServer();
            //the best algorithm for matrix problem
            Solver<string, string> *solver = new ObjectAdapter(new AStar<Cell *>());
            CacheManager *file = new FileCacheManager(5);
            ClientHandler *clientHandler = new MyClientHandler(file, solver);

            //open the connection and solve problems
            server->open(port, clientHandler);
        }
    };
}

#endif //EX4__BOOT_H_
