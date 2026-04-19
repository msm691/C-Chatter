/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** input_thread.c
*/

#include "client.h"

static void setup_input_box(client_env_t *env, char *prompt)
{
    werase(env->input_win);
    box(env->input_win, 0, 0);
    mvwprintw(env->input_win, 1, 1, prompt);
    wrefresh(env->input_win);
}

void *input_thread_main(void *arg)
{
    client_env_t *env = (client_env_t *)arg;
    packet_header_t hdr = {MSG_REQ, sizeof(msg_payload_t)};
    msg_payload_t msg;
    char buffer[MAX_MSG_LENGTH];

    memset(&msg, 0, sizeof(msg));
    setup_input_box(env, "Username: ");
    echo();
    wgetnstr(env->input_win, buffer, sizeof(msg.sender) - 1);
    strncpy(msg.sender, buffer, sizeof(msg.sender) - 1);
    
    while (1) {
        setup_input_box(env, "> ");
        memset(buffer, 0, sizeof(buffer));
        if (wgetnstr(env->input_win, buffer, sizeof(buffer) - 1) == ERR)
            break;
            
        if (strlen(buffer) > 0) {
            /* 1. Interception de la commande de déconnexion */
            if (strcmp(buffer, "/quit") == 0) {
                /* Ferme les flux de la socket pour débloquer le recv_thread */
                shutdown(env->sock, SHUT_RDWR);
                break;
            }
            
            memset(msg.text, 0, sizeof(msg.text));
            strncpy(msg.text, buffer, sizeof(msg.text) - 1);
            strncat(msg.text, "\n", sizeof(msg.text) - strlen(msg.text) - 1);
            
            write(env->sock, &hdr, sizeof(packet_header_t));
            write(env->sock, &msg, hdr.length);
            
            wprintw(env->msg_win, "[%s]: %s", msg.sender, msg.text);
            wrefresh(env->msg_win);
            wrefresh(env->input_win);
        }
    }
    return NULL;
}
