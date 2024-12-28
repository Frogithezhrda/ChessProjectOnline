#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "Socket.h"

#define PORT "8000"
#define BUFFER_SIZE 1024

int main() 
{
    WSADATA wsa;
    Socket server_socket;
    SOCKET client1_socket = NULL;
    SOCKET client2_socket = NULL;
    SOCKET current_player = NULL;
    SOCKET waiting_player = NULL;
    SOCKET temp = NULL;
    struct sockaddr_in client_addr;
    int addr_len = 0;
    char buffer[BUFFER_SIZE];
    int recv_len = 0;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cout << "error: " << std::endl << WSAGetLastError();
        return 1;
    }

    if (!server_socket.startServer(PORT))
    {
        std::cout << "Server socket fail" << std::endl;
        return 1;
    }
    //waiting for players
    std::cout << "Waiting For Players..." << std::endl;
    addr_len = sizeof(client_addr);
    //accepting the first player
    client1_socket = accept(server_socket.getSocket(), (struct sockaddr*)&client_addr, &addr_len);
    if (client1_socket == INVALID_SOCKET)
    {
        printf("Accept failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Player 1(White) connected.\n");
    //accepting the second player
    client2_socket = accept(server_socket.getSocket(), (struct sockaddr*)&client_addr, &addr_len);
    if (client2_socket == INVALID_SOCKET) 
    {
        printf("Accept failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Player 2(Black) connected.\n");
    //sending each their color
    send(client2_socket, "b", 2, 0);
    send(client1_socket, "w", 2, 0);

    // getting the current player and the waiting player
    current_player = client1_socket;
    waiting_player = client2_socket;

    while (true)
    {
        recv_len = recv(current_player, buffer, BUFFER_SIZE, 0);
        if (recv_len == SOCKET_ERROR || recv_len == 0)
        {
            printf("Connection lost.\n");
            break;
        }
        //removing making it a string
        buffer[recv_len] = '\0';
        printf("Received move: %s\n", buffer);

        send(waiting_player, buffer, recv_len, 0);

        // swap current and waiting players
        temp = current_player;
        current_player = waiting_player;
        waiting_player = temp;
    }
    //closing the sockets
    closesocket(client1_socket);
    closesocket(client2_socket);
    closesocket(server_socket.getSocket());
    WSACleanup();

    return 0;
}
