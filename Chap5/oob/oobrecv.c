//
// 带外数据 “紧急指针数据” 接收端
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE  1024
int main(int argc, char *agrv[])
{
    if(argc < 2){
        printf("argc error. argc: %d\n", argc);
        return 0;
    }

    const char *ip = argv[1];
    unsigned short int port = htos(atoi(argv[2]));
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.port = port;
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd > 0);
    int ret = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    assert(ret ==0 );
    ret = listen(sockfd, 5);

    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    int accept_sock = accept(sockfd, (struct sockaddr*) &client_addr, sizeof(client_addr));
    assert(accept_sock > 0);

    char buff[BUFF_SIZE];
    memset(buff, '\0', BUFF_SIZE);
    int count = recv(accept_sock, buff, BUFF_SIZE -1, 0);
    assert(count > 0);
    printf("get %d char(s). info =%s", count, buff);
    memset(buff, '\0', BUFF_SIZE);
    count = recv(accept_sock, buff, BUFF_SIZE - 1, 0);
    assert(count > 0);
    printf("get %d char(s). info =%s", count, buff);
    count = recv(accept_sock, buff, BUFF_SIZE - 1, 0);
    assert(count > 0);
    printf("get %d char(s). info =%s", count, buff);

    return 0;
}