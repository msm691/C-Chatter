/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** client.h
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <string.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdint.h>
    #include <pthread.h>
    #include <ncurses.h>
    #include "protocol.h"

    typedef struct client_env_s {
        int sock;
        WINDOW *msg_win;
        WINDOW *input_win;
    } client_env_t;

    int connect_to_server(const char *ip, uint16_t port);
    void *input_thread_main(void *arg);
    void *recv_thread_main(void *arg);
    void init_ui(client_env_t *env);
    void destroy_ui(client_env_t *env);

#endif
