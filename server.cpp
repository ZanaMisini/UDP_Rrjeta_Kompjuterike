#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <string>
#include <unordered_set>
#include <unordered_map>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#define BUFLEN 512
#define PORT 8888

using namespace std;

// Metoda per te shkruar ne file
void writeFile(const string& filename, const string& content)
{
    ofstream file(filename, ios::out | ios::binary);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
    else
    {
        cout << "Error opening file: " << filename << endl;
    }
}

// Metoda per append ne file
void appendFile(const string& filename, const string& content)
{
    ofstream file(filename, ios::out | ios::app | ios::binary);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
    else
    {
        cout << "Error opening file: " << filename << endl;
    }
}

int main()
{

    system("title UDP Server");

    // Inicializimi i winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        exit(0);
    }
    printf("Initialised.\n");

    // Krijimi i socket
    SOCKET server_socket;
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
    }
    printf("Socket created.\n");

    // Pregatitim strukturen sockaddr_in
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Lidhja
    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done.");
    // Ndihmojne per te mbajtur mend klientin e pare i cili i eshte casur serverit
    unordered_set<string> firstClient;
    unordered_map<string, sockaddr_in> clientAddresses;

    while (true)
    {
        printf("Waiting for data...");
        fflush(stdout);
        char message[BUFLEN] = {};

        // Per te marre te dhena nga klienti
        sockaddr_in clientAddr;
        int slen = sizeof(clientAddr);
        int message_len;
        if ((message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&clientAddr, &slen)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }

        printf("Received packet from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        string clientKey = string(inet_ntoa(clientAddr.sin_addr)) + ":" + to_string(ntohs(clientAddr.sin_port));
