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

       // Nqs klienti ka shkruar komanden "execute"
        if (strcmp(message, "execute") == 0)
        {
            if (firstClient.empty() || firstClient.count(clientKey) > 0) {

                // Gjenerimi i nje numri te rastesishem 1-100
                int magicNumber = rand() % 100 + 1;

                // Informojme klientin qe numri eshte gjeneruar
                string response = "Magic number generated. Try to guess! You have 5 guesses";
                if (sendto(server_socket, response.c_str(), response.size(), 0, (sockaddr*)&clientAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
                {
                    printf("sendto() failed with error code: %d", WSAGetLastError());
                    return 3;
                }

                int i = 5;
                // Klienti ka 5 mundesi per t'ia qelluar numrit te sakte
                while (i > 0)
                {
                    i--;
                    // Marrim pergjigjjen e klientit
                    char guessMessage[BUFLEN];
                    int guessMessageLength = recvfrom(server_socket, guessMessage, BUFLEN, 0, (sockaddr*)&clientAddr, &slen);
                    if (guessMessageLength == SOCKET_ERROR)
                    {
                        printf("recvfrom() failed with error code: %d", WSAGetLastError());
                        exit(0);
                    }

                    guessMessage[guessMessageLength] = '\0';

                    // Kthejme pergjigjjen ne integjer
                    int clientGuess = atoi(guessMessage);

                    // Nqs i'a ka qelluar numrit
                    if (clientGuess == magicNumber)
                    {
                       
                        string successMessage = "Congratulations! You guessed the magic number!";
                        if (sendto(server_socket, successMessage.c_str(), successMessage.size(), 0, (sockaddr*)&clientAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
                        {
                            printf("sendto() failed with error code: %d", WSAGetLastError());
                            return 3;
                        }

                        printf("Client guessed the correct number!\n");
                        break; 
                    }
                    else if (clientGuess > magicNumber && i != 0)
                    {
                        // Nqs numri eshte me i vogel
                        string errorMessage = "The magic number is smaller! Your tries: " + to_string(i);
                        if (sendto(server_socket, errorMessage.c_str(), errorMessage.size(), 0, (sockaddr*)&clientAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
                        {
                            printf("sendto() failed with error code: %d", WSAGetLastError());
                            return 3;
                        }
                    }
                    else if (clientGuess < magicNumber && i != 0)
                    {
                        // Nqs numri eshte me i madh
                        string errorMessage = "The magic number is bigger! Your tries: " + to_string(i);
                        if (sendto(server_socket, errorMessage.c_str(), errorMessage.size(), 0, (sockaddr*)&clientAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
                        {
                            printf("sendto() failed with error code: %d", WSAGetLastError());
                            return 3;
                        }
                    }
                    // Nqs klienti ka harxhuar te gjitha mundesite
                    if (i == 0)
                    {
                        string errorMessage = "You lost the game! The magic number was: " + to_string(magicNumber);
                        if (sendto(server_socket, errorMessage.c_str(), errorMessage.size(), 0, (sockaddr*)&clientAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
                        {
                            printf("sendto() failed with error code: %d", WSAGetLastError());
                            return 3;
                        }

                        printf("Client didn't guess the correct number\n");
                    }
                }
                firstClient.insert(clientKey); // Ky klient ka te drejte per execute

            }
            else {
                // Dergojme mesazh errori klientit se ai nuk eshte i pari dhe nuk ka te drejta per execute
                string errorMsg = "Magic Number Game not allowed for this client";
                if (sendto(server_socket, errorMsg.c_str(), errorMsg.size(), 0, (sockaddr*)&clientAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
                {
                    printf("sendto() failed with error code: %d", WSAGetLastError());
                    return 3;
                }
            }
        }
