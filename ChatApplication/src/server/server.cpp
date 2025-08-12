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

            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
            std::cout << "Client connected: " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

            std::thread clientThread(&TCPServer::handleClient, this, clientSocket);
            clientThread.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        stop();
    }
}

void TCPServer::handleClient(int clientSocket) {
    try {
        while (running) {
            std::string message = SocketUtils::receiveData(clientSocket);
            if (message.empty()) {
                break;
            }

            std::cout << "Received: " << message << std::endl;

            std::string response = "Server received: " + message;
            SocketUtils::sendData(clientSocket, response);
        }
    } catch (const std::exception& e) {
        std::cerr << "Client handling error: " << e.what() << std::endl;
    }

    SocketUtils::closeSocket(clientSocket);
    std::cout << "Client disconnected" << std::endl;
}

void TCPServer::stop() {
    if (running) {
        running = false;
        SocketUtils::closeSocket(serverSocket);
        std::cout << "Server stopped" << std::endl;
    }
}

