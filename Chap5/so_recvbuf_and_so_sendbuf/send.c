
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SEND_BUFF_SIZE    5000

const char *ip = "192.168.37.129";
const short int port = 12345;
int main()
{
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd > 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    int send_size = 2000;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &send_size, sizeof(send_size));
    assert(ret == 0);

    int sock_len = sizeof(send_size);
    ret = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &send_size, (socklen_t *) &sock_len);
    assert(ret == 0);
    printf("send buff size: %d\n", send_size);

    if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr) ) != -1 )
    {
        char buff[SEND_BUFF_SIZE];
        memset(buff, 'a', SEND_BUFF_SIZE -1);
        buff[SEND_BUFF_SIZE -1] = '\0';
        send(sockfd, buff, SEND_BUFF_SIZE, 0);
    }

    close(sockfd);

    return 0;
}