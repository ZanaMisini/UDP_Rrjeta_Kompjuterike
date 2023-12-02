
//Klienti
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#define BUFLEN 512
#define PORT 8888

int main()
{
    // Inicializojme winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    // Krijojme socket
    SOCKET client_socket;
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
        return 1;
    }
    printf("Socket created.\n");

    // Set up serverin me te dhenat e tij
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (true)
    {
        // Marrim inputin e userit
        char command[BUFLEN];
        printf("Enter message: ");
        fgets(command, BUFLEN, stdin);

        // Largojme newline para se te dergojme mesazhin
        command[strcspn(command, "\n")] = '\0';

        // Dergojme mesazhin tek serveri
        if (sendto(client_socket, command, strlen(command), 0, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 1;
        }


    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}
