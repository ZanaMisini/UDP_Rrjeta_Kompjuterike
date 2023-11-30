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

     if (strncmp(message, "file r: ", 8) == 0)
        {
            
            string filename = message + 8;

           
            ifstream file(filename, ios::binary);
            if (!file.is_open())
            {
                cout << "Error opening file: " << filename << endl;

                
                string errorMsg = "Error opening file: " + filename;
                if (sendto(server_socket, errorMsg.c_str(), errorMsg.size(), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
                {
                    printf("sendto() failed with error code: %d", WSAGetLastError());
                    return 3;
                }
                continue; 
            }

            
            string fileContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();

            
            if (sendto(server_socket, fileContent.c_str(), fileContent.size(), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("sendto() failed with error code: %d", WSAGetLastError());
                return 3;
            }
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

        if (strncmp(message, "file w: ", 8) == 0)
        {
            if (allowedWriteClients.empty() || allowedWriteClients.count(clientKey) > 0)
            {
                string fileWriteCommand = message + 8;
                size_t pos = fileWriteCommand.find(' ');
                if (pos != string::npos)
                {
                    string filename = fileWriteCommand.substr(0, pos);
                    string content = fileWriteCommand.substr(pos + 1);

                    writeFile(filename, content);

                    string successMsg = "Content written to file: " + filename;
                    if (sendto(server_socket, successMsg.c_str(), successMsg.size(), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
                    {
                        printf("sendto() failed with error code: %d", WSAGetLastError());
                        return 3;
                    }

                    allowedWriteClients.insert(clientKey);
                }
            }

            else
            {
                string errorMsg = "Write operation not allowed for this client";
                if (sendto(server_socket, errorMsg.c_str(), errorMsg.size(), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
                {
                    printf("sendto() failed with error code: %d", WSAGetLastError());
                    return 3;
                }
            }
        }
            else if (strncmp(message, "file a: ", 8) == 0)
        {
            if (firstClient.empty() || firstClient.count(clientKey) > 0)
            {
                string fileAppendCommand = message + 8;
                size_t pos = fileAppendCommand.find(' ');
                if (pos != string::npos)
                {
                    string filename = fileAppendCommand.substr(0, pos);
                    string content = fileAppendCommand.substr(pos + 1);

                    appendFile(filename, content);

                    string successMsg = "Content appended to file: " + filename;
                    if (sendto(server_socket, successMsg.c_str(), successMsg.size(), 0, (sockaddr*)&clientAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
                    {
                        printf("sendto() failed with error code: %d", WSAGetLastError());
                        return 3;
                    }

                    firstClient.insert(clientKey); 
                }
            }
         else
        {
            printf("Client says: %s\n", message);

            char serverMessage[BUFLEN];
            printf("Enter message to client: ");
            cin.getline(serverMessage, BUFLEN);

            if (sendto(server_socket, serverMessage, strlen(serverMessage), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("sendto() failed with error code: %d", WSAGetLastError());
                return 3;
            }
        }
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
        

  
        printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        printf("Data: %s\n", message);

        cin.getline(message, BUFLEN);

     
    }

    

    closesocket(server_socket);
    WSACleanup();
}
