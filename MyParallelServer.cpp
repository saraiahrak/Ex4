//
// Created by dekel on 15/01/2020.
//

#include "MyParallelServer.h"
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <vector>
#include <fstream>
#include <thread>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"

using namespace std;

MyParallelServer::MyParallelServer() {
  this->stop = false;
}

//Set the server socket after creation
void MyParallelServer::setStop() {
  MyParallelServer::stop = true;
}

//Set the server socket after creation
void MyParallelServer::setServerSocket(int s) {
  MyParallelServer::socketfd = s;
}

void MyParallelServer::setTimeOut() {
  timeval timeout;
  timeout.tv_sec = 120;
  timeout.tv_usec = 0;
  setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
}

//opens the server
void MyParallelServer::openServerSocket(int p, ClientHandler* c) {
  //create socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    //error creating socket
    cerr << "Could not create a socket" << endl;
  }

  //bind socket to IP address
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(p);

  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    //error binding
    cerr << "Could not bind the socket to an IP" << endl;
  }

  //reading from client in separate thread
  thread serverThread(start, socketfd, address, c);
  serverThread.detach();
}

//Open the server socket
void MyParallelServer::start(int socketfd, sockaddr_in address, ClientHandler* c) {
  //listen to port
  this->counter = 0;
  while (!stop) {
    if (listen(socketfd, 5) == -1) {
      cerr << "Error during listening command" << endl;
    } else {
      cout << "Server is now listening ..." << endl;
    }
    //set the time for waiting to client
    setTimeOut();
    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
    while (client_socket < 0) {
      cerr << "Error accepting client, trying again" << endl;
      client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
    }

    //close(socketfd);

    this->counter++;

    cout << "connected to client" << endl;
    c->handleClient(client_socket);
    c = new ClientHandler();
    thread???


  }
  close(socketfd); //closing the listening socket
}
