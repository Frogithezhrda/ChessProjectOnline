#include "Socket.h"
#include <iostream>
#include <string>
#include <winsock2.h>

Socket::Socket()
{
    _socket = INVALID_SOCKET;
    _result = nullptr;
    ZeroMemory(&_hints, sizeof(_hints));
    _isActive = false;
}

Socket::~Socket()
{
    closeSocket();
}
bool Socket::startServer(const std::string& port)
{
    int iResult = WSAStartup(MAKEWORD(2, 2), &_wsaData);
    if (iResult != 0)
    {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return false;
    }

    _hints.ai_family = AF_INET;
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_protocol = IPPROTO_TCP;
    _hints.ai_flags = AI_PASSIVE; // For binding to any available IP

    iResult = getaddrinfo(nullptr, port.c_str(), &_hints, &_result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed: " << iResult << std::endl;
        WSACleanup();
        return false;
    }

    _socket = socket(_result->ai_family, _result->ai_socktype, _result->ai_protocol);
    if (_socket == INVALID_SOCKET)
    {
        std::cerr << "Can't create socket" << std::endl;
        freeaddrinfo(_result);
        WSACleanup();
        return false;
    }

    iResult = bind(_socket, _result->ai_addr, (int)_result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        freeaddrinfo(_result);
        closesocket(_socket);
        WSACleanup();
        return false;
    }

    iResult = listen(_socket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(_socket);
        WSACleanup();
        return false;
    }

    freeaddrinfo(_result);
    _isActive = true;
    return true;
}

SOCKET Socket::acceptClient()
{
    if (_socket == INVALID_SOCKET) {
        std::cerr << "Server socket is not active" << std::endl;
        return INVALID_SOCKET;
    }

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    SOCKET client_socket = accept(_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
        return INVALID_SOCKET;
    }

    std::cout << "Client connected." << std::endl;
    return client_socket;
}

bool Socket::connectToServer(const std::string& ipAddress, const std::string& port)
{
    int iResult = WSAStartup(MAKEWORD(2, 2), &_wsaData);
    if (iResult != 0)
    {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return false;
    }

    _hints.ai_family = AF_INET;
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(ipAddress.c_str(), port.c_str(), &_hints, &_result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed: " << iResult << std::endl;
        WSACleanup();
        return false;
    }

    _socket = socket(_result->ai_family, _result->ai_socktype, _result->ai_protocol);
    if (_socket == INVALID_SOCKET)
    {
        std::cerr << "Can't create socket" << std::endl;
        freeaddrinfo(_result);
        WSACleanup();
        return false;
    }

    iResult = connect(_socket, _result->ai_addr, (int)_result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        std::cerr << "Unable to connect to server: " << WSAGetLastError() << std::endl;
        closesocket(_socket);
        _socket = INVALID_SOCKET;
        freeaddrinfo(_result);
        WSACleanup();
        return false;
    }

    freeaddrinfo(_result);
    _isActive = true;
    return true;
}

int Socket::sendData(const std::string& data)
{
    if (_socket == INVALID_SOCKET) {
        std::cerr << "Socket is not connected" << std::endl;
        return -1;
    }

    int iResult = send(_socket, data.c_str(), (int)data.size(), 0);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        return -1;
    }

    std::cout << "Sent data: " << data << std::endl;
    return iResult;
}

std::string Socket::receiveData()
{
    if (_socket == INVALID_SOCKET) {
        std::cerr << "Socket is not connected" << std::endl;
        return "";
    }

    char buffer[512];
    int iResult = recv(_socket, buffer, sizeof(buffer), 0);
    if (iResult > 0) {
        buffer[iResult] = '\0';  // Null-terminate the received data
        std::cout << "Received data: " << buffer << std::endl;
        return std::string(buffer);
    }
    else if (iResult == 0) {
        std::cout << "Connection closed" << std::endl;
        return "";
    }
    else {
        std::cerr << "Recv failed: " << WSAGetLastError() << std::endl;
        return "";
    }
}
SOCKET Socket::getSocket() const
{
    return _socket;
}
void Socket::closeSocket()
{
    if (_socket != INVALID_SOCKET)
    {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
    }
    if (_isActive) {
        WSACleanup();
        _isActive = false;
    }
}
