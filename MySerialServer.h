//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H
#include <netinet/in.h>
#include "ServerSide.h"
#include <sys/socket.h>
#include <unistd.h>


//class Server;

/**
 * Class MySerialServer
 * Inherites from ServerSide
 * */

class MySerialServer : public server_side::Server {
public:

    //local client socket
    static bool isStop;

    //Constructor
    MySerialServer();

//    void setServerSocket(int s);

    void open(int p, ClientHandler *c);

    static void start(int socketfd, sockaddr_in address, ClientHandler *c);

    void stop();

    static void setTimeOut(int socketfd);

    void setStop();


};


#endif //EX4_MYSERIALSERVER_H
