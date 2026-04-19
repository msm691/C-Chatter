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

    int server_main(int argc, char **argv);
    int init_server(uint16_t port, int *server_fd);
    int set_non_blocking(int fd);
    
    // Ajout de la nouvelle fonction
    int run_server_loop(int server_fd);

#endif /* !SERVER_H_ */
