//
// Created by dekel on 14/01/2020.
//
#include "MySerialServer.h"
#include <thread>

using namespace std;

bool MySerialServer::isStop;

MySerialServer::MySerialServer() {
    MySerialServer::isStop = false;
}

//Set the server socket after creation
void MySerialServer::setStop() {
    MySerialServer::isStop = true;
}

void MySerialServer::setTimeOut(int socketfd) {
    timeval timeout;
    timeout.tv_sec = 120;
    timeout.tv_usec = 0;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
}

//opens the server
void MySerialServer::open(int p, ClientHandler *c) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error creating socket
        cerr << "Could not create a socket" << endl;
    }

    setSocket(socketfd);

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
    serverThread.join();
    stop();

}

//Open the server socket
void MySerialServer::start(int socketfd, sockaddr_in address, ClientHandler *c) {
    //set the time for waiting to client
    setTimeOut(socketfd);
    //listen to port
    while (!MySerialServer::isStop) {
        if (listen(socketfd, 5) == -1) {
            cerr << "Error during listening command" << endl;
        } else {
            cout << "ServerSide is now listening ..." << endl;
        }
        // accepting a client
        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
        while (client_socket < 0) {
            if (errno == EWOULDBLOCK | errno == EAGAIN) {
                cerr << "Time out" << endl;
                setStop();
                break;
            }
            cout << "couldn't connected to client, try again..." << endl;
            client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
        }
        cout << "connected to client" << endl;
        c->handleClient(client_socket);
    }
}

void MySerialServer::stop() {
    close(this->socketfd);
}

void MySerialServer::setSocket(int socket) {
    this->socketfd = socket;
}
