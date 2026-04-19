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

void broadcast_message(server_t *server, int sender_fd, 
    packet_header_t *hdr, msg_payload_t *msg)
{
    int dest_fd;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        dest_fd = server->clients[i];
        if (dest_fd != -1 && dest_fd != sender_fd) {
            write(dest_fd, hdr, sizeof(packet_header_t));
            write(dest_fd, msg, hdr->length);
        }
    }
}
