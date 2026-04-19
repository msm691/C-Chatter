/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** events.c
*/

#include "server.h"

static int handle_new_connection(int server_fd)
{
    int client_fd;
    struct sockaddr_in addr;
    socklen_t len;

    len = sizeof(addr);
    client_fd = accept(server_fd, (struct sockaddr *)&addr, &len);
    if (client_fd < 0) {
        return -1;
    }
    printf("New connection from %s:%d\n", inet_ntoa(addr.sin_addr),
        ntohs(addr.sin_port));
    
    close(client_fd);
    return 0;
}

int run_server_loop(int server_fd)
{
    fd_set readfds;
    int max_fd;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_fd = server_fd;

        if (select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
            return -1;
        }

        if (FD_ISSET(server_fd, &readfds)) {
            handle_new_connection(server_fd);
        }
    }
    return 0;
}
