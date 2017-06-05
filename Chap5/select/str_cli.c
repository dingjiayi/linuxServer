/* 
* @Author: dingjiayi
*/

#include <stdio.h>
#include <assert.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <typesizes.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <netinet/in.h>

#define SERV_PORT  (12345)
#define LISTENQ     (1024)
#define BUFF_SIZE   (1024)

int main() {

    int i, n, ret;
    int maxi, maxfd, listenfd, connfd, sockfd;
    int nready;
    socklen_t clilen =0;
    char remote[INET_ADDRSTRLEN +1];
    char buf[BUFF_SIZE];
    struck sockaddr_in client_addr, server_addr;
    fd_set readset, allset;
    short int client[FD_SETSIZE];

    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >=0);

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(listenfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    assert(ret >=0);

    ret = listen(listenfd, LISTENQ);
    assert(ret == 0);

    maxfd = listenfd;       /* initialize */
    maxi = -1;              /* index into client[] array */
    for (i = 0; i < FD_SETSIZE; ++i)
    {
        client[i] = -1;    /* -1 indicates available entry */
    }
    memset(remote, '\0', sizeof(remote));

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (; ;)
    {
        readset = allset;
        nready = select(maxfd + 1, &readset, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &readset)){    /* new client connection */
            printf("listening socket readable\n");
            sleep(5);
            clilen = sizeof(client_addr);
            connfd = accept(listenfd, (struct sockaddr*) &client_addr, sizeof(client_addr));
            printf("new client: %s, port %d\n", inet_ntop(AF_INET, &client_addr.sin_addr, remote, INET_ADDRSTRLEN), ntohs(client_addr.sin_port));

            for (i = 0; i < FD_SETSIZE; ++i)
            {
                if (client[i] < 0){
                    client[i] = connfd;     /* save descriptor */
                    break;
                }
            }
            if (i == FD_SETSIZE){
                perror("too many clients");
            }

            FD_SET(connfd, &allset);    /* add new descriptor to set */
            if (connfd > maxfd)
                maxfd = connfd;         /* for select */
            if (i > maxi)
                maxi = i;               /* max index in client[] array */
            if (--nready <= 0)
                continue;               /* no more readable descriptors */
        }

        for (i = 0; i <= maxi; i++){    /* check all clients for data */
            if ( (sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &readset)) {
                if ( (n = read(sockfd, buf, BUFF_SIZE)) == 0 ){
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }else
                    write(sockfd, buf, n);

                if (--nready <=0)
                    break;
            }
        }

    }

    return 0;
}