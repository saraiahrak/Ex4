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

    static bool isStop;

    //local client socket
    int socketfd;

    //Constructor
    MySerialServer();


    void open(int p, ClientHandler *c) override;

    static void start(int socketfd, sockaddr_in address, ClientHandler *c);

    void stop() override;

    static void setTimeOut(int socketfd);

    static void setStop();

    void setSocket(int socket);
};


#endif //EX4_MYSERIALSERVER_H
