/*
 * socket_utils.cpp
 *
 *  Created on: Aug 12, 2025
 *      Author: ashik-g-k
 */


#include "socket_utils.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

int SocketUtils::createSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        throw std::runtime_error("Failed to create socket");
    }
    return sock;
}

void SocketUtils::bindSocket(int socket, int port) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Bind failed");
    }
}

void SocketUtils::listenSocket(int socket, int backlog) {
    if (listen(socket, backlog) < 0) {
        throw std::runtime_error("Listen failed");
    }
}

int SocketUtils::acceptConnection(int serverSocket, sockaddr_in& clientAddr) {
    socklen_t clientLen = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
    if (clientSocket < 0) {
        throw std::runtime_error("Accept failed");
    }
    return clientSocket;
}

void SocketUtils::connectToServer(int socket, const std::string& ip, int port) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address/Address not supported");
    }

    if (connect(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) {
        throw std::runtime_error("Connection failed");
    }
}

void SocketUtils::sendData(int socket, const std::string& data) {
    if (send(socket, data.c_str(), data.size(), 0) < 0) {
        throw std::runtime_error("Send failed");
    }
}

std::string SocketUtils::receiveData(int socket, int bufferSize) {
    char buffer[bufferSize];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesRead < 0) {
        throw std::runtime_error("Receive failed");
    }
    return std::string(buffer, bytesRead);
}

void SocketUtils::closeSocket(int socket) {
    close(socket);
}

