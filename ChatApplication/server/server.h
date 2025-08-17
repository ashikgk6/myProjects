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
#include <unordered_map>
#include <memory>

#include "thread_pool.h"

class TCPServer {
public:
    TCPServer(int port, size_t thread_pool_size = 4);
    ~TCPServer();

    void start();
    void handleClient(int clientSocket, const sockaddr_in& clientAddr);
    void stop();

private:
    int serverSocket;
    int port;
    std::atomic<bool> running;
    sockaddr_in serverAddr;
    std::unordered_map<int, std::string> clientUsernames;
    std::unique_ptr<ThreadPool> threadPool;
    std::mutex serverMutex;
};


#endif /* SERVER_SERVER_H_ */
