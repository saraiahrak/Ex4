//
// Created by dekel on 15/01/2020.
//

#ifndef EX4__MYPARALLELSERVER_H_
#define EX4__MYPARALLELSERVER_H_

#include "MyTestClientHandler.h"
#include "Server.h"
#include <netinet/in.h>

using namespace std;

class MyParallelServer : public Server {

 public:

  //local client socket
  static int socketfd;
  static int counter;
  static bool stop;

  //Constructor
  MyParallelServer();

  void setServerSocket(int s);

  static void openServerSocket(int p);

  void start(int socketfd, sockaddr_in address, ClientHandler* c);

  void setTimeOut();

  void setStop();
};

#endif //EX4__MYPARALLELSERVER_H_
