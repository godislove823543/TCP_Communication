//
//  Server.hpp
//  server
//
//  Created by programer on 2023/7/24.
//

#ifndef Server_hpp
#define Server_hpp

#include <string>
#include <stdio.h>
#include <pthread.h>
#include <vector>
class Server
{
public:
    Server(int port);
    ~Server();
    void Start();
    int clientSocket=0;
private:
    int port;
    int serverSocket;
    pthread_t process;
    std::vector<int> socketList;
    
//    void ProcessClient(int clientSocket);
 static void *ProcessClient(void *);
};
#endif /* Server_hpp */
