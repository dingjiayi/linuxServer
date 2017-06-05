/* 
* @Author: dingjiayi
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>

const char *SERVER_IP = "168.1.1.1";
const short int SERVER_PORT = 12345;
const short int process_count = 3;

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

            itoa(getpid(), send_buf, 10);
            printf("Write %d char(s): %s\n", strlen(send_buf), send_buf);
            n = send(sockfd, send_buf, strlen(send_buf), 0);
            assert(n == strlen(send_buf));
            n = recv(sockfd, recv_buf, 20-1, 0);
            printf("Read %d char(s)：%s\n", n, recv_buf);

            close(sockfd);

        }
    }

    if (pid !=0){
        int stat_val = 0;
        wait_pid(&stat_val);
    }

    return 0;
}