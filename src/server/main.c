/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** main.c
*/

#include <stdio.h>
#include <signal.h>
#include "server.h"

int main(int argc, char **argv)
{
    server_t server;
    uint16_t port;

    (void)argc;
    (void)argv;

    signal(SIGPIPE, SIG_IGN);

    port = 8080;
    if (init_server(port, &server) == -1) {
        printf("Error: Could not initialize server.\n");
        return 84;
    }
    printf("Epollaris Server started on port %d...\n", port);
    
    if (run_server_loop(&server) == -1) {
        printf("Error: Server loop crashed.\n");
        return 84;
    }
    
    return 0;
}
