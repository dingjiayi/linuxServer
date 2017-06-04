

#include <stdio.h>
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define RECV_BUFF_SIZE  1024
const char *ip = "192.168.37.129";
const short int port = 12345;
int main()
{
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int recv_size = 50;
    int sockopt_len = sizeof(recv_size);
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recv_size, sizeof(sockopt_len));
    assert(ret == 0);

    ret = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recv_size, (socklen_t *) &sockopt_len);
    assert(ret == 0);
    printf("recv buff size: %d\n",  recv_size);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    ret = bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    assert(ret == 0);

    ret = listen(sockfd, 5);
    assert(ret == 0);

    struct sockaddr_in client_addr;
    int socklen = sizeof(client_addr);
    int client_sock = accept(sockfd, (struct sockaddr*) &client_addr, &socklen);
    assert(client_sock >= 0);

    char buff[RECV_BUFF_SIZE];
    memset(buff, '0', RECV_BUFF_SIZE);

    int read_len = 0;
    while((read_len = recv(client_sock, buff, RECV_BUFF_SIZE -1, 0)) > 0)
    {
        printf("recv %d character\n", read_len);
    }

    close(client_sock);
    close(sockfd);

    return 0;
}