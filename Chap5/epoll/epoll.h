//
// Created by gz0507 on 2017/6/29.
//

#ifndef LINUXSERVER_EPOLL_H
#define LINUXSERVER_EPOLL_H

#include <sys/types.h>
#include <sys/socket.h>
#include <bits/socket.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

#define SERVER_IP  "192.168.1.12"
#define SERVER_PORT  12345
#define MAX_EVENT_NUMBER  1024


int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);

    return new_option;
}


#endif //LINUXSERVER_EPOLL_H
