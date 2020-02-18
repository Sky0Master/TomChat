#include "tcp.h"

void TCP_Client::Send(const char * data)
{
    send(sock_client, data, strlen(data), 0);
}

int TCP_Client::Connect()
{
    if (connect(sock_client, (struct sockaddr*) & serv_add, sizeof(serv_add) ) == INVALID_SOCKET) 
    {
        err = 3;
        return 0;
    }
            state = 1;
            return 1;
        }

void TCP_Client::Recv(char* data)
{
    int end=recv(sock_client, data, size, 0);
    data[end] = '\0';
}

TCP_Client::TCP_Client(const char* serv_ip, int serv_port)
{
    WORD w = MAKEWORD(2, 2);
    WSADATA wsa;
    if (WSAStartup(w, &wsa) != 0) 
    {
        err = 1; 
        return;
    }

    serv_add.sin_family = AF_INET;
    serv_add.sin_port = htons(serv_port);
    serv_add.sin_addr.S_un.S_addr = inet_addr(serv_ip);  
    //inet_pton(AF_INET,serv_ip,&serv_add.sin_addr);   //新函数
    sock_client = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == sock_client) 
    {
        err = 2;
        return;
    }
}