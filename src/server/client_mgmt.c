/*
** EPITECH PROJECT, 2026
** TeleChat
** File description:
** client_mgmt.c
*/

#include "server.h"

void init_client_list(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i] = -1;
        memset(server->usernames[i], 0, MAX_NAME_LENGTH);
        memset(server->channels[i], 0, MAX_NAME_LENGTH);
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
        memset(server->usernames[index], 0, MAX_NAME_LENGTH);
        memset(server->channels[index], 0, MAX_NAME_LENGTH);
    }
}

void broadcast_message(server_t *server, int sender_fd, 
    packet_header_t *hdr, msg_payload_t *msg)
{
    int dest_fd;
    char *s_chan = "";

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] == sender_fd)
            s_chan = server->channels[i];
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        dest_fd = server->clients[i];
        if (dest_fd != -1 && dest_fd != sender_fd) {
            if (strcmp(server->channels[i], s_chan) == 0) {
                write(dest_fd, hdr, sizeof(packet_header_t));
                write(dest_fd, msg, hdr->length);
            }
        }
    }
}

int send_direct_message(server_t *server, const char *target, 
    packet_header_t *hdr, msg_payload_t *msg)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] != -1 && 
            strcmp(server->usernames[i], target) == 0) {
            write(server->clients[i], hdr, sizeof(packet_header_t));
            write(server->clients[i], msg, hdr->length);
            return 1;
        }
    }
    return 0;
}
