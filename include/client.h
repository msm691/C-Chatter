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
    #include "protocol.h"

    int connect_to_server(const char *ip, uint16_t port);
    void *input_thread_main(void *arg);
    void *recv_thread_main(void *arg);

#endif /* !CLIENT_H_ */
