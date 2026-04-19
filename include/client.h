/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** client.h
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <stdio.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdint.h>
    #include "protocol.h"

    int connect_to_server(const char *ip, uint16_t port);
    int client_main(int argc, char **argv);

#endif /* !CLIENT_H_ */