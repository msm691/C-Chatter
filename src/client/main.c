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
    pthread_t recv_tid;
    pthread_t input_tid;

    (void)argc;
    (void)argv;
    sock = connect_to_server("127.0.0.1", 8080);
    if (sock < 0) {
        printf("Error: Could not connect to server.\n");
        return 84;
    }
    printf("Connected to Epollaris Server! You can start typing...\n");
    pthread_create(&recv_tid, NULL, recv_thread_main, &sock);
    pthread_create(&input_tid, NULL, input_thread_main, &sock);
    pthread_join(recv_tid, NULL);
    
    close(sock);
    return 0;
}
