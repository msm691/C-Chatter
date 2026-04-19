/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** main.c
*/

#include "client.h"

int main(int argc, char **argv)
{
    int sock;

    (void)argc;
    (void)argv;
    sock = connect_to_server("127.0.0.1", 8080);
    if (sock < 0) {
        printf("Error: Could not connect to server.\n");
        return 84;
    }
    printf("Connected to Epollaris Server!\n");
    sleep(2);
    close(sock);
    return 0;
}