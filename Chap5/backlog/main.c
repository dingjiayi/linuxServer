/*处于ESTABLISHED状态的连接比 listen的第二个参数大1
 * 如果有多的连接过来，则处于SYN_RCVD状态
 * */

#include "backlog.h"

static bool stop=false;
static void handle_term(int sig)
{
    stop=true;
}

int main(int argc, char* argv[])
{
    signal(SIGTERM, handle_term);
    if (argc < 3)
    {
        printf("usage:%s ip_address port_number backlog\n", argv[0]);
        return 1;
    }

    const char*ip=argv[1];
    int port=atoi(argv[2]);
    int backlog=atoi(argv[3]);

//    创建socket ipv4
    int sc = socket(PF_INET, SOCK_STREAM, 0);
    assert(sc > 0);
//    命名socket
    struct sockaddr_in sc_addr;
    bzero(&sc_addr, sizeof(sc_addr));
    sc_addr.sin_family=AF_INET;
    inet_pton(AF_INET, ip, &sc_addr.sin_addr);
    sc_addr.sin_port = htons(port);
    int ret = bind(sc, (struct sockaddr *)&sc_addr, sizeof(sc_addr));
    assert(ret != -1);
//    监听socket
    ret = listen(sc, backlog);
    assert(ret != -1);

    /* loop wait connect, until SIGTERM break it */

    while (!stop)
    {
        sleep(1);
    }

    /* close socket */
    close(sc);

    return 0;
}