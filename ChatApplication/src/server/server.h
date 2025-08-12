/*
 * server.h
 *
 *  Created on: Aug 12, 2025
 *      Author: ashik-g-k
 */

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_


#include <string>
#include <netinet/in.h>

class TCPServer {
public:
    TCPServer(int port);
    ~TCPServer();

    void start();
    void handleClient(int clientSocket);
    void stop();

private:
    int serverSocket;
    int port;
    bool running;
    sockaddr_in serverAddr;
};


#endif /* SERVER_SERVER_H_ */
