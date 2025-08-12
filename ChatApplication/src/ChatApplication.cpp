//============================================================================
// Name        : ChatApplication.cpp
// Author      : Ashik G K
// Version     :
// Copyright   : Your copyright notice
// Description : Chat Server
//============================================================================

#include <iostream>
#include <string>
#include <thread>
#include "server/server.h"
#include "client/client.h"

void runServer(int port) {
    try {
        TCPServer server(port);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
    }
}

void runClient(const std::string& serverIP, int serverPort) {
    try {
        TCPClient client(serverIP, serverPort);
        client.connectToServer();

        while (true) {
            std::cout << "Enter message (or 'exit' to quit): ";
            std::string message;
            std::getline(std::cin, message);

            if (message == "exit") {
                break;
            }

            client.sendMessage(message);
            std::string response = client.receiveResponse();
            std::cout << "Server response: " << response << std::endl;
        }

        client.disconnect();
    } catch (const std::exception& e) {
        std::cerr << "Client exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Choose mode:\n";
    std::cout << "1. Server\n";
    std::cout << "2. Client\n";
    std::cout << "Enter choice: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Clear the newline character

    const int PORT = 8080;
    const std::string SERVER_IP = "127.0.0.1";

    if (choice == 1) {
        runServer(PORT);
    } else if (choice == 2) {
        runClient(SERVER_IP, PORT);
    } else {
        std::cerr << "Invalid choice" << std::endl;
        return 1;
    }

    return 0;
}
