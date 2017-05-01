
/* 对于connect到服务器的客户端，如果掉线、退出，服务器调用accept的时候，还会选择到对应的连接吗
 * 也就是服务器调用accept会成功返回吗？
 * */
#include "accept.h"

int main(int argc, char *argv[])
{
    if(argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    /* 暂停20秒以等待客户端的连接和相关操作（掉线或者推出）完成 */
    sleep(20);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*) &client, &client_addrlength);
    if(connfd < 0)
    {
        printf("errno is: %d\n", errno);
    }else
    {
        /* 接受连接成功，打印客户端的ip和端口 */
        char remote[INET_ADDRSTRLEN];
        printf("connected with ip: %s and port: %d\n", inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN), ntohs(client.sin_port));
        close(connfd);
    }

    close(sock);
    return 0;

}