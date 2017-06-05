/* 
* @Author: dingjiayi
* @Date:   2017-06-05 14:44:51
* @comment: 查看 SO_SNDLOWAT 和 SO_RCVLOWAT的默认值
*/

#include <stdio.h>
#include <sys/socket.h>
#include <assert.h>
#include <arpa/inet.h>

const char *ip = "127.0.0.1";
const short int port = 12345;
int main() {
    
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >=0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);
    int ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret == 0);
    listen(sockfd, 5);

    int snd_low_at = 0;
    int len = sizeof(snd_low_at);
    ret = getsockopt(sockfd, SOL_SOCKET, SO_SNDLOWAT, (void*) &snd_low_at, (socklen_t*) &len);
    assert(ret == 0);
    printf("DEFAULT SO_SNDLOWAT =%d\n", snd_low_at);

    int rcv_low_at = 0;
    len = sizeof(rcv_low_at);
    ret = getsockopt(sockfd, SOL_SOCKET, SO_RCVLOWAT, (void*) &snd_low_at, (socklen_t*) &len);
    assert(ret == 0);
    printf("DEFAULT SO_RCVLOWAT =%d\n", rcv_low_at);
    close(sockfd);

    return 0;
}