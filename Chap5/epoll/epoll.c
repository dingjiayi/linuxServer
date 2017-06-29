
#include "epoll.h"

int main()
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    memeset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    socklen_t addrlen = sizeof(server_addr);
    int ret = bind(sock, (struct sockaddr*)&server_addr, addrlen);
    assert(ret > 0);
    ret = listen(sock, 5);
    assert(ret > 0);

    event_poll events[MAX_EVENT_NUMBER];
    int epoll_fd = epoll_create(5);
    assert(epoll_fd > -1);





    return 0;
}
