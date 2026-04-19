/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** client_mgmt.c
*/

#include <unistd.h>
#include "server.h"

void init_client_list(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i] = -1;
    }
}

int add_client(server_t *server, int client_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] == -1) {
            server->clients[i] = client_fd;
            return 0;
        }
    }
    close(client_fd);
    return -1;
}

void remove_client(server_t *server, int index)
{
    if (server->clients[index] != -1) {
        close(server->clients[index]);
        server->clients[index] = -1;
    }
}
