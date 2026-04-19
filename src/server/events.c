/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** events.c
*/

#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"

static void setup_fd_set(server_t *server, fd_set *readfds, int *max_fd)
{
    FD_ZERO(readfds);
    FD_SET(server->fd, readfds);
    *max_fd = server->fd;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] != -1) {
            FD_SET(server->clients[i], readfds);
        }
        if (server->clients[i] > *max_fd) {
            *max_fd = server->clients[i];
        }
    }
}

static void handle_new_connection(server_t *server)
{
    int client_fd;
    struct sockaddr_in addr;
    socklen_t len;

    len = sizeof(addr);
    client_fd = accept(server->fd, (struct sockaddr *)&addr, &len);
    if (client_fd < 0)
        return;
    if (add_client(server, client_fd) == -1) {
        printf("Server full: connection rejected.\n");
    } else {
        printf("New connection from %s:%d\n", inet_ntoa(addr.sin_addr),
            ntohs(addr.sin_port));
    }
}

static void check_clients_activity(server_t *server, fd_set *readfds)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] != -1 && FD_ISSET(server->clients[i], readfds)) {
            handle_client_message(server, i);
        }
    }
}

int run_server_loop(server_t *server)
{
    fd_set readfds;
    int max_fd;

    while (1) {
        setup_fd_set(server, &readfds, &max_fd);
        if (select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
            return -1;
        }
        if (FD_ISSET(server->fd, &readfds)) {
            handle_new_connection(server);
        }
        check_clients_activity(server, &readfds);
    }
    return 0;
}
