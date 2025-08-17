/*
 * client.h
 *
 *  Created on: Aug 12, 2025
 *      Author: ashik-g-k
 */

#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_


#include <string>

class TCPClient {
public:
    TCPClient(const std::string& serverIP, int serverPort);
    ~TCPClient();

    void connectToServer();
    void sendMessage(const std::string& message);
    std::string receiveResponse();
    void disconnect();
    void setUsername(const std::string& username);
    std::string getUsername() const;

private:
    int clientSocket;
    std::string serverIP;
    int serverPort;
    bool connected;
    std::string username;
};


#endif /* CLIENT_CLIENT_H_ */
