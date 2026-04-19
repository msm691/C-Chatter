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
        if (b_read <= 0) {
            return b_read;
        }
        total += b_read;
    }
    return 1;
}

int handle_client_message(server_t *server, int client_idx)
{
    packet_header_t hdr;
    msg_payload_t msg;
    int fd = server->clients[client_idx];

    if (read_exact(fd, &hdr, sizeof(packet_header_t)) <= 0) {
        printf("Client %d disconnected.\n", fd);
        remove_client(server, client_idx);
        return -1;
    }
    if (hdr.length > 0 && hdr.length <= sizeof(msg_payload_t)) {
        if (read_exact(fd, &msg, hdr.length) <= 0) {
            remove_client(server, client_idx);
            return -1;
        }
        printf("Client %d [Type %d] says: %s\n", fd, hdr.type, msg.text);
    }
    return 0;
}
