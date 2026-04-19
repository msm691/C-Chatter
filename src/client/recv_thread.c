/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** recv_thread.c
*/

#include "client.h"

static int read_exact(int fd, void *buf, size_t n)
{
    size_t total = 0;
    ssize_t b_read;

    while (total < n) {
        b_read = read(fd, (char *)buf + total, n - total);
        if (b_read <= 0)
            return -1;
        total += b_read;
    }
    return 1;
}

void *recv_thread_main(void *arg)
{
    int sock = *(int *)arg;
    packet_header_t hdr;
    msg_payload_t msg;

    while (1) {
        if (read_exact(sock, &hdr, sizeof(packet_header_t)) < 0) {
            break;
        }
        if (hdr.length > 0 && hdr.length <= sizeof(msg_payload_t)) {
            if (read_exact(sock, &msg, hdr.length) < 0)
                break;
            printf("[%s]: %s", msg.sender, msg.text);
        }
    }
    printf("\n[Disconnected from server]\n");
    return NULL;
}
