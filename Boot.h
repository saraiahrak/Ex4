//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__BOOT_H_
#define EX4__BOOT_H_

#include "MySerialServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"

namespace boot {
class Main {
 public:
  Main() {}

  void main(int port) {
    //creates new server
    server_side::Server *server = new MySerialServer();
    //creates a new solver
    Solver<string, string> *solver = new StringReverser();
    //creates cache manager file
    CacheManager *file = new FileCacheManager(5);
    //creates new handler
    ClientHandler *clientHandler = new MyTestClientHandler(file, solver);

    //open the connection and solve problems
    server->open(port, clientHandler);
  }
};
}

#endif //EX4__BOOT_H_
