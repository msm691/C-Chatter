/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** init.c
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stddef.h>
#include "server.h"

int set_non_blocking(int fd)
{
    int flags;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        return -1;
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        return -1;
    }
    return 0;
}

int create_server_socket(uint16_t port)
{
    int fd;
    struct sockaddr_in addr;
    int opt;

    opt = 1;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        return -1;
    }
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        return -1;
    }
    return fd;
}

int init_server(uint16_t port, server_t *server)
{
    server->fd = create_server_socket(port);
    if (server->fd < 0) {
        return -1;
    }
    if (set_non_blocking(server->fd) < 0 || listen(server->fd, SOMAXCONN) < 0) {
        return -1;
    }
    init_client_list(server);
    return 0;
}
