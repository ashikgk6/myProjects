/*
 * server.cpp
 *
 *  Created on: Aug 12, 2025
 *      Author: ashik-g-k
 */


#include "server.h"
#include "../common/socket_utils.h"
#include <iostream>
#include <thread>
#include <vector>
#include <csignal>

TCPServer::TCPServer(int port) : port(port), running(false) {
    serverSocket = SocketUtils::createSocket();
}

TCPServer::~TCPServer() {
    stop();
}

void TCPServer::start() {
    try {
        SocketUtils::bindSocket(serverSocket, port);
        SocketUtils::listenSocket(serverSocket);
        running = true;

        std::cout << "Server started on port " << port << std::endl;

        while (running) {
            sockaddr_in clientAddr{};
            int clientSocket = SocketUtils::acceptConnection(serverSocket, clientAddr);

            std::thread clientThread(&TCPServer::handleClient, this, clientSocket, clientAddr);
            clientThread.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        stop();
    }
}

void TCPServer::handleClient(int clientSocket, const sockaddr_in& clientAddr) {
    try {
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);

        // First message should be the username
        std::string usernameMessage = SocketUtils::receiveData(clientSocket);
        if (usernameMessage.find("USERNAME:") == 0) {
            std::string username = usernameMessage.substr(9);
            clientUsernames[clientSocket] = username;
            std::cout << "Client " << clientIP << " connected as " << username << std::endl;
        } else {
            clientUsernames[clientSocket] = "anonymous";
            std::cout << "Client " << clientIP << " connected without username" << std::endl;
        }

        while (running) {
            std::string message = SocketUtils::receiveData(clientSocket);
            if (message.empty()) {
                break;
            }

            std::string username = clientUsernames[clientSocket];
            std::cout << username << " (" << clientIP << "): " << message << std::endl;

            std::string response = username + "> " + message;
            SocketUtils::sendData(clientSocket, response);
        }
    } catch (const std::exception& e) {
        std::cerr << "Client handling error: " << e.what() << std::endl;
    }

    std::string username = clientUsernames[clientSocket];
    std::cout << username << " disconnected" << std::endl;
    clientUsernames.erase(clientSocket);
    SocketUtils::closeSocket(clientSocket);
}

void TCPServer::stop() {
    if (running) {
        running = false;
        SocketUtils::closeSocket(serverSocket);
        std::cout << "Server stopped" << std::endl;
    }
}

