/*
 * client.cpp
 *
 *  Created on: Aug 12, 2025
 *      Author: ashik-g-k
 */


#include "client.h"
#include "../common/socket_utils.h"
#include <iostream>

TCPClient::TCPClient(const std::string& serverIP, int serverPort)
    : serverIP(serverIP), serverPort(serverPort), connected(false) {
    clientSocket = SocketUtils::createSocket();
}

TCPClient::~TCPClient() {
    disconnect();
}

void TCPClient::connectToServer() {
    try {
        SocketUtils::connectToServer(clientSocket, serverIP, serverPort);
        connected = true;
        std::cout << "Connected to server " << serverIP << ":" << serverPort << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        throw;
    }
}

void TCPClient::sendMessage(const std::string& message) {
    if (!connected) {
        throw std::runtime_error("Not connected to server");
    }

    try {
        SocketUtils::sendData(clientSocket, message);
    } catch (const std::exception& e) {
        std::cerr << "Send error: " << e.what() << std::endl;
        disconnect();
        throw;
    }
}

std::string TCPClient::receiveResponse() {
    if (!connected) {
        throw std::runtime_error("Not connected to server");
    }

    try {
        return SocketUtils::receiveData(clientSocket);
    } catch (const std::exception& e) {
        std::cerr << "Receive error: " << e.what() << std::endl;
        disconnect();
        throw;
    }
}

void TCPClient::disconnect() {
    if (connected) {
        SocketUtils::closeSocket(clientSocket);
        connected = false;
        std::cout << "Disconnected from server" << std::endl;
    }
}

