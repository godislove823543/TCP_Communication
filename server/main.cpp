//
//  main.cpp
//  server
//
//  Created by programer on 2023/7/24.
//

#include <iostream>
#include "Server.hpp"

int main(int argc, const char * argv[]) {
    Server server(12345);
    server.Start();
    return 0;
}
