/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** ui.c
*/

#include "client.h"

void init_ui(client_env_t *env)
{
    int max_y;
    int max_x;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, max_y, max_x);
    env->msg_win = newwin(max_y - 3, max_x, 0, 0);
    env->input_win = newwin(3, max_x, max_y - 3, 0);
    scrollok(env->msg_win, TRUE);
    box(env->input_win, 0, 0);
    mvwprintw(env->input_win, 1, 1, "> ");
    wrefresh(env->msg_win);
    wrefresh(env->input_win);
}

void destroy_ui(client_env_t *env)
{
    delwin(env->msg_win);
    delwin(env->input_win);
    endwin();
}
