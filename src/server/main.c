/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** main.c
*/

#include <stdio.h>
#include "server.h"

int main(int argc, char **argv)
{
    int server_fd;
    uint16_t port;

    (void)argc;
    (void)argv;
    port = 8080;
    if (init_server(port, &server_fd) == -1) {
        printf("Error: Could not initialize server.\n");
        return 84;
    }
    printf("Epollaris Server started on port %d...\n", port);
    return 0;
}
