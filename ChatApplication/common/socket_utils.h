/*
 * socket_utils.h
 *
 *  Created on: Aug 12, 2025
 *      Author: ashik-g-k
 */

#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class SocketUtils {
public:
    static int createSocket();
    static void bindSocket(int socket, int port);
    static void listenSocket(int socket, int backlog = 5);
    static int acceptConnection(int serverSocket, sockaddr_in& clientAddr);
    static void connectToServer(int socket, const std::string& ip, int port);
    static void sendData(int socket, const std::string& data);
    static std::string receiveData(int socket, int bufferSize = 1024);
    static void closeSocket(int socket);
};

#endif // SOCKET_UTILS_H
