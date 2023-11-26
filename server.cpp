#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 

#define BUFLEN 512
#define PORT 8888

int main()
{
    system("title UDP Server");

    sockaddr_in server, client;

   
    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        exit(0);
    }
    printf("Initialised.\n");

    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
        {
            printf("Could not create socket: %d", WSAGetLastError());
        }
    
   
    SOCKET server_socket;
  
    printf("Socket created.\n");

    if(bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
        {
            printf("Bind faild with erorr code: %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
        
   
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

 
    puts("Bind done.");

    if(sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 3;
        }
                

    while (true)
    {
        printf("Waiting for data...");
        fflush(stdout);
        char message[BUFLEN] = {};

        int message_len;
        int slen = sizeof(sockaddr_in);
        if (message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }
                

  
        printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        printf("Data: %s\n", message);

        cin.getline(message, BUFLEN);

     
    }

    closesocket(server_socket);
    WSACleanup();
}
