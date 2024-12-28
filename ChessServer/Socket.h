#pragma once
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "8888"
#define BUFFER_SIZE 1024

class Socket
{
public:
    Socket();
    ~Socket();

    void closeSocket();
    bool startServer(const std::string& port);
    SOCKET acceptClient();
    bool connectToServer(const std::string& ipAddress, const std::string& port);
    int sendData(const std::string& data);
    std::string receiveData();
    SOCKET getSocket() const;
private:
    WSADATA _wsaData;
    SOCKET _socket;
    struct addrinfo* _result;
    struct addrinfo _hints;
    bool _isActive;

};