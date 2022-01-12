////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////

#include "Server.h"


using namespace std;

/**
 * Server constructor, creates the communication channel(socket)
 * @param port to run communication with client on
 */
Server::Server(int port)throw (const char*) {
    //make system call to linux to create communication channel(socket)
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
    server.sin_port = htons(port);
    //call bind and handle error
    if(0 > bind(socketFD,(struct sockaddr*)&server, sizeof(server)))
        throw "bind failure";
    //ask permission to listen to clients
    if(0 > listen(socketFD, 10))
        throw "listen failure";

}

/**
 * run communication through socket in a thread
 * @param ch a client handler instance
 */
void Server::start(ClientHandler& ch)throw(const char*){
    //running in background
    isRunning = true;
    t = new thread([&ch, this](){
        //cout<<"server is waiting for client"<<endl;
        //save aside size of clientFD struct
        while(isRunning){
            socklen_t clientSize = sizeof(client);
            //implement all the details about the client that connected
            alarm(2);
            //put all the information about in clientFD
            int clientFD = accept(socketFD, (struct sockaddr*)&client, &clientSize);
            alarm(0);
            if (0 > clientFD){
                throw "failed to accept";
            }
            //cout<<"accepted client"<<endl;
            //client handler responsible for talking to client
            //give client handler the client id we got from accept
            ch.handle(clientFD);
            //correspondence ended so we need to close all the channels
            close(clientFD);
        }
        close(socketFD);
    });
}

/**
 * signal to stop the running of communication
 */
void Server::stop(){
    isRunning = false;
    t->join(); // do not delete this!
}

/**
 * server destructor
 */
Server::~Server() {
}


