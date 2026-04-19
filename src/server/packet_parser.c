/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** packet_parser.c
*/

#include "server.h"
#include "protocol.h"

static int read_exact(int fd, void *buf, size_t n)
{
    size_t total = 0;
    ssize_t b_read;

    while (total < n) {
        b_read = read(fd, (char *)buf + total, n - total);
        if (b_read == 0) return 0;
        if (b_read < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) continue;
            return -1;
        }
        total += b_read;
    }
    return 1;
}

static void send_system_event(server_t *server, int fd, const char *user, const char *act)
{
    packet_header_t hdr = {MSG_REQ, sizeof(msg_payload_t)};
    msg_payload_t msg;

    memset(&msg, 0, sizeof(msg));
    strcpy(msg.sender, "Server");
    snprintf(msg.text, sizeof(msg.text), "%s %s the chat.\n", user, act);
    broadcast_message(server, fd, &hdr, &msg);
}

int handle_client_message(server_t *server, int client_idx)
{
    packet_header_t hdr;
    msg_payload_t msg;
    int fd = server->clients[client_idx];

    if (read_exact(fd, &hdr, sizeof(packet_header_t)) <= 0) {
        if (server->usernames[client_idx][0] != '\0')
            send_system_event(server, fd, server->usernames[client_idx], "left");
        printf("Client %d disconnected.\n", fd);
        remove_client(server, client_idx);
        return -1;
    }
    if (read_exact(fd, &msg, hdr.length) <= 0) return -1;
    if (hdr.type == LOGIN_REQ) {
        strncpy(server->usernames[client_idx], msg.sender, MAX_NAME_LENGTH - 1);
        send_system_event(server, fd, msg.sender, "joined");
    } else {
        printf("[%s] says: %s", msg.sender, msg.text);
        broadcast_message(server, fd, &hdr, &msg);
    }
    return 0;
}
