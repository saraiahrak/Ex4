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
            Solver<string, string> *solver = new ObjectAdapter(new DFS<Cell *>());
            CacheManager *file = new FileCacheManager(5);
            ClientHandler* clientHandler = new MyClientHandler(file, solver);

//            //creates new server
//            server_side::Server *server = new MySerialServer();
//            //creates a new solver
//            Solver<string, string> *solver = new StringReverser();
//            //creates cache manager file
//            CacheManager *file = new FileCacheManager(5);
//            //creates new handler
//            ClientHandler *clientHandler = new MyTestClientHandler(file, solver);

            //open the connection and solve problems
            server->open(port, clientHandler);
        }
    };
}

#endif //EX4__BOOT_H_
