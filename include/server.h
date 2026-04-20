/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdint.h>
    #include <sys/select.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include "protocol.h"
    #include <errno.h>

    #define MAX_CLIENTS 30

    typedef struct server_s {
        int fd;
        int clients[MAX_CLIENTS];
        char usernames[MAX_CLIENTS][MAX_NAME_LENGTH];
    } server_t;

    int init_server(uint16_t port, server_t *server);
    int set_non_blocking(int fd);
    int run_server_loop(server_t *server);
    void init_client_list(server_t *server);
    int add_client(server_t *server, int client_fd);
    void remove_client(server_t *server, int index);
    int handle_client_message(server_t *server, int client_idx);
    void broadcast_message(server_t *server, int sender_fd, 
        packet_header_t *hdr, msg_payload_t *msg);
    void broadcast_message(server_t *server, int sender_fd, 
        packet_header_t *hdr, msg_payload_t *msg);
    int send_direct_message(server_t *server, const char *target, 
        packet_header_t *hdr, msg_payload_t *msg);

#endif
