/*
 * server.cpp
 *
 *  Created on: Aug 12, 2025
 *      Author: ashik-g-k
 */


#include "server.h"
#include <iostream>
#include <csignal>
#include "socket_utils.h"

TCPServer::TCPServer(int port, size_t thread_pool_size)
    : port(port), running(false), threadPool(std::make_unique<ThreadPool>(thread_pool_size)) {
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

        std::cout << "Server started on port " << port
                  << " with thread pool size " << threadPool->getTaskCount() << std::endl;

        while (running) {
            sockaddr_in clientAddr{};
            socklen_t clientLen = sizeof(clientAddr);
            int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);

            if (clientSocket < 0) {
                if (running) {
                    std::cerr << "Accept failed, continuing..." << std::endl;
                }
                continue;
            }

            threadPool->enqueue([this, clientSocket, clientAddr]() {
                this->handleClient(clientSocket, clientAddr);
            });

            std::cout << "Active tasks in pool: " << threadPool->getTaskCount() << std::endl;
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
            {
                std::lock_guard<std::mutex> lock(serverMutex);
                clientUsernames[clientSocket] = username;
            }
            std::cout << "Client " << clientIP << " connected as " << username << std::endl;
        } else {
            {
                std::lock_guard<std::mutex> lock(serverMutex);
                clientUsernames[clientSocket] = "anonymous";
            }
            std::cout << "Client " << clientIP << " connected without username" << std::endl;
        }

        while (running) {
            std::string message = SocketUtils::receiveData(clientSocket);
            if (message.empty()) {
                break;
            }

            std::string username;
            {
                std::lock_guard<std::mutex> lock(serverMutex);
                username = clientUsernames[clientSocket];
            }

            std::cout << username << " (" << clientIP << "): " << message << std::endl;

            std::string response = username + "> " + message;
            SocketUtils::sendData(clientSocket, response);
        }
    } catch (const std::exception& e) {
        std::cerr << "Client handling error: " << e.what() << std::endl;
    }

    std::string username;
    {
        std::lock_guard<std::mutex> lock(serverMutex);
        username = clientUsernames[clientSocket];
        clientUsernames.erase(clientSocket);
    }

    std::cout << username << " disconnected" << std::endl;
    SocketUtils::closeSocket(clientSocket);
}

void TCPServer::stop() {
    if (running) {
        running = false;
        SocketUtils::closeSocket(serverSocket);
        threadPool->waitAll();
        std::cout << "Server stopped" << std::endl;
    }
}

