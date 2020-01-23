//
// Created by dekel on 15/01/2020.
//

#ifndef EX4__MYPARALLELSERVER_H_
#define EX4__MYPARALLELSERVER_H_

#include "ServerSide.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;


//class Server;

/**
 * Class MySerialServer
 * Inherites from ServerSide
 **/
class MyParallelServer : public server_side::Server {
 public:

  static bool isStop;
  //local client socket
  int socketfd;
  //count the clients
  static int counter;

  //Constructor
  MyParallelServer();

  ~MyParallelServer() = default;

  void open(int p, ClientHandler *c) override;

  static void start(int socketfd, sockaddr_in address, ClientHandler *c);

  void stop() override;

  static void setTimeOut(int socketfd);

  static void setStop();

  void setSocket(int socket);

  static void handle(int client_socket, ClientHandler *c);
};

#endif //EX4__MYPARALLELSERVER_H_
