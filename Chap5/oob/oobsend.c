
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>


int main(int argc, char *argv[])
{
    const char *confg_ip = "192.168.37.129";
    const int port = 12345;


    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd > 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, confg_ip, &server_addr.sin_addr);
    int ret = connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    assert(ret == 0);

    const char* normal_data1 = "123";
    const char* oob_data = "abc";
    const char* normal_data2 = "456";

    send(sockfd, normal_data1, strlen(normal_data1), 0);
    send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
    send(sockfd, normal_data2, strlen(normal_data2), 0);

    return 0;
}