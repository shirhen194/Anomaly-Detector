////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////

#ifndef SERVER_H_
#define SERVER_H_
//TODO: check what ifndef need to be what they gave or what i did
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <csignal>
#include "commands.h"
#include "CLI.h"

using namespace std;


// edit your ClientHandler interface here:
class ClientHandler {
public:
    virtual void handle(int clientID) = 0;
};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler : public ClientHandler {
public:
    virtual void handle(int clientID) {
        SocketIO socketIo(clientID);
        CLI cli(&socketIo);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    thread *t; // the thread to run the start() method in

    // you may add data members
    sockaddr_in server;
    sockaddr_in client;
    int socketFD;
    bool isRunning;

public:
    Server(int port) throw(const char *);

    virtual ~Server();

    void start(ClientHandler &ch) throw(const char *);

    void stop();
};

#endif /* SERVER_H_ */

//#endif //MAIN_CPP_SERVER_H
