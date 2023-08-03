//
//  Server.hpp
//  server
//
//  Created by programer on 2023/7/24.
//

#ifndef Server_hpp
#define Server_hpp

#include <string>
#include <pthread.h>
#include <vector>

class Server
{
public:
    Server(int port);
    ~Server();
    //�}�l���A�����禡
    void Start();
    //�Ω��x�s�Ȥ�ݪ�socket�ܼ�
    int clientSocket=0;
private:
    int port;
    int serverSocket; 
    //�x�s�Ȥ��socket���V�q
    std::vector<int> socketList;

    pthread_t process;
    //�b��������B�z�Ȥ�ݪ��s�u
    static void *ProcessClient(void *);
};
#endif /* Server_hpp */
