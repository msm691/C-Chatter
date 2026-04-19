/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** input_thread.c
*/

#include "client.h"

void *input_thread_main(void *arg)
{
    int sock = *(int *)arg;
    packet_header_t hdr;
    msg_payload_t msg;
    char buffer[MAX_MSG_LENGTH];

    hdr.type = MSG_REQ;
    hdr.length = sizeof(msg_payload_t);
    memset(&msg, 0, sizeof(msg));
    
    printf("Username: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(msg.sender, buffer, sizeof(msg.sender) - 1);
    }
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        memset(msg.text, 0, sizeof(msg.text));
        strncpy(msg.text, buffer, sizeof(msg.text) - 1);
        write(sock, &hdr, sizeof(packet_header_t));
        write(sock, &msg, hdr.length);
    }
    return NULL;
}
