//
//  Server.cpp
//  server
//
//  Created by programer on 2023/7/24.
//

#include "Server.hpp"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
Server::Server(int port):port(port),serverSocket(-1)
{}
Server::~Server()
{
    if(serverSocket != -1)
    {
        close(serverSocket);
    }
}
void Server::Start()
{
    //create sock
    serverSocket=socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket == -1)
    {
        perror("建立伺服器的socket失敗");
        exit(EXIT_FAILURE);
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=INADDR_ANY;
    serverAddr.sin_port=htons(port);
    
    //bind
    if(::bind(serverSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr))==-1)
    {
        perror("綁定socket失敗");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    
    //listen for incoming connections
    if(listen(serverSocket,SOMAXCONN) == -1)
    {
        perror("監聽失敗");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    
    cout<< "伺服器正在監聽" << port << endl;

    while(true)
    {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen=sizeof(clientAddr);
        
        //accept client connection
        int clientSocket=::accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if(clientSocket == -1)
        {
            perror("接受客戶端連線失敗");
            continue;
        }
        socketList.push_back(clientSocket);
        //handle client chat in a new thread
        pthread_create(&process, NULL, ProcessClient, this);
  //      thread(&Server::ProcessClient,this,clientSocket).detach();
        
    }
}

void *Server::ProcessClient(void *object)
{
    char buf[4096];
    
    Server *server=(Server *)object;
    while(true)
    {
        memset(buf,0,4096);
        
        //recv msg from client
        int bytesRecv = recv(server->socketList.back(),buf,4095,0);
        if(bytesRecv == -1)
        {
            perror("接收訊息失敗");
            break;
        }
        else if(bytesRecv == 0)
        {
            cout << "客戶斷開連線" << endl;
            close(server->socketList.back());
            server->socketList.pop_back();
            break;
            
        }
        //process msg
        cout << "收到客戶訊息：" << buf << endl;
        for(int i=0;i<server->socketList.size();i++)
        {
            send(server->socketList[i],buf,bytesRecv,0);
        }
        sleep(3);
    }
    
    return nullptr;
}
