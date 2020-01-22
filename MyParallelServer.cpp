////
//// Created by dekel on 15/01/2020.
////
//
//#include "MyParallelServer.h"
//#include <unistd.h>
//#include <string>
//#include <sys/socket.h>
//#include <iostream>
//#include <netinet/in.h>
//#include <thread>
//
//using namespace std;
//
//MyParallelServer::MyParallelServer() {
//  this->isStop = false;
//  this->counter = 0;
//}
//
////Set the server socket after creation
//void MyParallelServer::setStop() {
//  MyParallelServer::isStop = true;
//}
//
//void MyParallelServer::setTimeOut(int socketfd) {
//  timeval timeout;
//  timeout.tv_sec = 120;
//  timeout.tv_usec = 0;
//  setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
//}
//
////opens the server
//void MyParallelServer::open(int p, ClientHandler* c) {
//  //create socket
//  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
//  if (socketfd == -1) {
//    //error creating socket
//    cerr << "Could not create a socket" << endl;
//  }
//  setSocket(socketfd);
//
//  //bind socket to IP address
//  sockaddr_in address;
//  address.sin_family = AF_INET;
//  address.sin_addr.s_addr = INADDR_ANY;
//  address.sin_port = htons(p);
//
//  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
//    //error binding
//    cerr << "Could not bind the socket to an IP" << endl;
//  }
//
//  if (listen(socketfd, 5) < 0) {
//    cerr << "Error during listening command" << endl;
//  } else {
//    cout << "Server is now listening ..." << endl;
//  }
//  //start to accept clients
//  this->start(socketfd, address, c);
//}
//
////Open the server socket
//void MyParallelServer::start(int socketfd, sockaddr_in address, ClientHandler* c) {
//  //set the time for waiting to client
//  setTimeOut(socketfd);
//  //listen to port
//  while (!MyParallelServer::isStop) {
//    // accepting a client
//    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
//    if (client_socket < 0) {
//      if (errno == EWOULDBLOCK || errno == EAGAIN) {
//        cerr << "Time out" << endl;
//        setStop();
//        break;
//      }
//      cerr << "Error accepting client, trying again" << endl;
//    }
//
//    MyParallelServer::counter += 1;
//    cout << "connected to client" << endl;
//
//
//    //reading from client in separate thread
////    pthread_t handle;
////    pthread_create(&handle, nullptr, &MyParallelServer::handle, client_socket, *c);
//
//    thread serverThread(handle, client_socket, c);
//    serverThread.join();
//
//    if (MyParallelServer::counter == 0) {
//      stop();
//    }
//  }
//}
//
//
//void MyParallelServer::stop() {
//  close(this->socketfd);
//}
//
//void MyParallelServer::setSocket(int socket) {
//  this->socketfd = socket;
//}
//
//void MyParallelServer::handle(int client_socket, ClientHandler* c) {
//  c->handleClient(client_socket);
//  MyParallelServer::counter -= 1;
//}
