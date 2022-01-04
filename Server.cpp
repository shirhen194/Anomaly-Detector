////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////

#include "Server.h"
#include <sys/socket.h>
#include <netintet/in.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

/**
 *
 * @param port
 */
Server::Server(int port)throw (const char*) {
    //make system call to linux to create comuunication channel(socket)
    //we want to work in TCP
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    //handle error
    if(socketFD < 0){
        //TODO:destruct here
        throw "socket failure";
    }
    //bind ip(our address) and port to the socket we got
    //we recognize the socket by the socketFD we got
    //cast sockaddr_in to sockaddr
    //ip version 4
    server.sin_family = AF_INET;
    //server ip (localhost)
    //everythiמg that comes from the different channels of the socket,
    // goes here
    server.sin_addr.s_addr = INADDR_ANY;
    //cast int port to network
    server.port = htons(port);
    //call bind and handle error
    if(0 > bind(socketFD,(struct sockaddr*)&server, sizeof(server)))
        throw "bind failure";
    //ask permission to listen to clients
    if(0 > listen(socketFD, 10))
        throw "listen failure";

}

/**
 *
 * @param ch
 */
void Server::start(ClientHandler& ch)throw(const char*){
    //runing in background
    isRunning = true;
    t = new thread([&ch, this](){
        cout<<"server is waiting for client"<<endl;
        //save aside size of clientFD struct
        socklen_t clientSize = sizeof(clientFD);
        while(isRunning){
            alarm(1);
            //implement all the details about the client that connected
            //put all the information about in clientFD
            int aClient = accept(socketFD, (struct sockaddr*)&clientFD, &clientSize);
            alarm(0);
            if (0 > aClient)
                throw "failed to accept";
            cout<<"accepted client"<<endl;
            //client handler responsible of talking to client
            //give client handler the client id we got from accept
            ch.handle(aClient);
            //correspondence ended so we need to close all the channels
            close(clientFD);
        }
        close(socketFD);
    });
}

/**
 *
 */
void Server::stop(){
    isRunning = false;
    t->join(); // do not delete this!
}

Server::~Server() {
}


