#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 

#define SERVER "127.0.0.1"  // or "localhost" - ip address of UDP server
#define BUFLEN 512  // max length of answer
#define PORT 8888  // the port on which to listen for incoming data

    WSADATA ws;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");


int main()
{
    system("title UDP Client");

//VJOSA
// start communication
    while (true)
    {
        char message[BUFLEN];
        printf("Enter message: ");
        cin.getline(message, BUFLEN);

