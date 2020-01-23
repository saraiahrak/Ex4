//
// Created by dekel on 15/01/2020.
//

#ifndef EX4__MYCLIENTHANDLER_H_
#define EX4__MYCLIENTHANDLER_H_

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "MySerialServer.h"

class MyClientHandler : public ClientHandler {
public:
  CacheManager *cacheManager;
  Solver<string, string> *solver;

  MyClientHandler(CacheManager *c, Solver<string, string> *s);

  void handleClient(int clientSocket) override;

  ClientHandler* clone(){
    return new MyClientHandler(this->cacheManager, this->solver->clone());
  }
};


#endif //EX4__MYCLIENTHANDLER_H_
