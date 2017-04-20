//
// Created by gz0507 on 2017/4/20.
//

#include "backlog.h"
int main(int argc, char* argv[])
{
//    创建socket
    int sc = socket(PF_INET, SOCK_STREAM, 0);
//    命名socket
    struct sockaddr_in sc_addr;
    bind(sc, (struck sockaddr *)&sc_addr, sizeof(sc_addr));
//    监听socket
    listen(sc, 10);
    return 0;
}