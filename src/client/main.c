/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** main.c
*/

#include "client.h"

int main(int argc, char **argv)
{
    client_env_t env;
    pthread_t recv_tid;
    pthread_t input_tid;

    (void)argc;
    (void)argv;
    env.sock = connect_to_server("127.0.0.1", 8080);
    if (env.sock < 0) {
        printf("Error: Could not connect to server.\n");
        return 84;
    }
    init_ui(&env);
    wprintw(env.msg_win, "Connected to Epollaris Server!\n");
    wrefresh(env.msg_win);
    pthread_create(&recv_tid, NULL, recv_thread_main, &env);
    pthread_create(&input_tid, NULL, input_thread_main, &env);
    pthread_join(recv_tid, NULL);
    destroy_ui(&env);
    close(env.sock);
    return 0;
}
