/*
* @Author: dingjiayi
* @comment: 利用fork 创建多个进程，模拟客户端和select服务器“交互”
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

const char *SERVER_IP = "192.168.37.129";
const short int SERVER_PORT = 12345;
const short int process_count = 2;

void itoa(int i,char*string)
{
    int power,j;
    j=i;
    for(power=1;j>=10;j/=10)
        power*=10;
    for(;power>0;power/=10)
    {
        *string++='0'+i/power;
        i%=power;
    }
    *string='\0';
}

int main() {

    int i = 0;
    pid_t pid;

    for (i = 0; i < process_count; ++i)
    {
        pid = fork();
        if (pid > 0){      /* parent */
            continue;
        }else{              /* child */
            struct sockaddr_in server_addr;
            int sockfd;
            int n = 0;
            char send_buf[20];
            char recv_buf[20];
            memset(send_buf, '\0', 20);
            sockfd = socket(PF_INET, SOCK_STREAM, 0);
            assert(sockfd >=0);

            bzero(&server_addr, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
            server_addr.sin_port = htons(SERVER_PORT);

            connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
            assert(sockfd >=0);
            unsigned short int port = 0;
            struct sockaddr_in client_addr;
            int clilen = sizeof(client_addr);
            int ret = getsockname(sockfd, (struct sockaddr*) &client_addr, &clilen);
            assert(ret == 0);


            itoa(getpid(), send_buf);
            printf("Client: ip: %s  port: %d Write %ld char(s): %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), strlen(send_buf), send_buf);
            n = send(sockfd, send_buf, strlen(send_buf), 0);
            assert(n == strlen(send_buf));
            n = recv(sockfd, recv_buf, 20-1, 0);
            printf("Client: ip: %s  port: %d Read %d char(s)：%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), n, recv_buf);

            close(sockfd);

        }
    }

    if (pid !=0){
        int stat_val = 0;
        wait(&stat_val);
        sleep(3);
    }

    return 0;
}
