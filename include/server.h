/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdint.h>
    #include "protocol.h"

    int server_main(int argc, char **argv);
    int init_server(uint16_t port, int *server_fd);
    int set_non_blocking(int fd);

#endif /* !SERVER_H_ */
