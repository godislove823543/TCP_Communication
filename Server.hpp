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
    //開始伺服器的函式
    void Start();
    //用於儲存客戶端的socket變數
    int clientSocket=0;
private:
    int port;
    int serverSocket; 
    //儲存客戶端socket的向量
    std::vector<int> socketList;

    pthread_t process;
    //在執行緒中處理客戶端的連線
    static void *ProcessClient(void *);
};
#endif /* Server_hpp */
