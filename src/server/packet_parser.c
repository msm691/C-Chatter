/*
** EPITECH PROJECT, 2026
** TeleChat
** File description:
** packet_parser.c
*/

#include "server.h"
#include "protocol.h"

static int read_exact(int fd, void *buf, size_t n)
{
    size_t total = 0;
    ssize_t b_read;

    while (total < n) {
        b_read = read(fd, (char *)buf + total, n - total);
        if (b_read == 0) return 0;
        if (b_read < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) continue;
            return -1;
        }
        total += b_read;
    }
    return 1;
}

static void send_system_event(server_t *server, int fd, const char *user, const char *act)
{
    packet_header_t hdr = {MSG_REQ, sizeof(msg_payload_t)};
    msg_payload_t msg;

    memset(&msg, 0, sizeof(msg));
    strcpy(msg.sender, "Server");
    snprintf(msg.text, sizeof(msg.text), "%s %s the chat.\n", user, act);
    broadcast_message(server, fd, &hdr, &msg);
}

static void send_system_direct(int fd, const char *text)
{
    packet_header_t hdr = {MSG_REQ, sizeof(msg_payload_t)};
    msg_payload_t msg;

    memset(&msg, 0, sizeof(msg));
    strcpy(msg.sender, "Server");
    strncpy(msg.text, text, MAX_MSG_LENGTH - 1);
    write(fd, &hdr, sizeof(packet_header_t));
    write(fd, &msg, hdr.length);
}

static void process_user_list(server_t *server, int fd)
{
    char buffer[MAX_MSG_LENGTH] = "En ligne: ";
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] != -1 && server->usernames[i][0]) {
            strncat(buffer, server->usernames[i], 
                MAX_MSG_LENGTH - strlen(buffer) - 1);
            strncat(buffer, " ", 2);
        }
    }
    strncat(buffer, "\n", 2);
    send_system_direct(fd, buffer);
}

static void process_private_msg(server_t *server, msg_payload_t *msg)
{
    char target[MAX_NAME_LENGTH] = {0};
    char *space = strchr(msg->text + 5, ' ');
    packet_header_t hdr = {MSG_REQ, sizeof(msg_payload_t)};
    char buffer[MAX_MSG_LENGTH];

    if (!space) return;
    strncpy(target, msg->text + 5, space - (msg->text + 5));
    snprintf(buffer, sizeof(buffer), "[Private] %s", space + 1);
    strncpy(msg->text, buffer, MAX_MSG_LENGTH - 1);
    send_direct_message(server, target, &hdr, msg);
}

static void process_join_channel(server_t *server, int idx, msg_payload_t *msg)
{
    char target[MAX_NAME_LENGTH] = {0};
    char buffer[MAX_MSG_LENGTH];

    if (strlen(msg->text) > 6) {
        strncpy(target, msg->text + 6, MAX_NAME_LENGTH - 1);
        target[strcspn(target, "\n")] = 0;
        strncpy(server->channels[idx], target, MAX_NAME_LENGTH - 1);
        snprintf(buffer, sizeof(buffer), "Bienvenue dans %s\n", target);
        send_system_direct(server->clients[idx], buffer);
    }
}

int handle_client_message(server_t *server, int client_idx)
{
    packet_header_t hdr;
    msg_payload_t msg;
    int fd = server->clients[client_idx];

    if (read_exact(fd, &hdr, sizeof(packet_header_t)) <= 0) {
        if (server->usernames[client_idx][0] != '\0')
            send_system_event(server, fd, server->usernames[client_idx], "left");
        printf("Client %d disconnected.\n", fd);
        remove_client(server, client_idx);
        return -1;
    }
    if (read_exact(fd, &msg, hdr.length) <= 0) return -1;
    if (hdr.type == LOGIN_REQ) {
        strncpy(server->usernames[client_idx], msg.sender, MAX_NAME_LENGTH - 1);
        strcpy(server->channels[client_idx], "#general");
        send_system_event(server, fd, msg.sender, "joined");
    } else {
        if (strncmp(msg.text, "/msg ", 5) == 0) {
            process_private_msg(server, &msg);
        } else if (strncmp(msg.text, "/users", 6) == 0) {
            process_user_list(server, fd);
        } else if (strncmp(msg.text, "/join ", 6) == 0) {
            process_join_channel(server, client_idx, &msg);
        } else {
            printf("[%s] says: %s", msg.sender, msg.text);
            broadcast_message(server, fd, &hdr, &msg);
        }
    }
    return 0;
}
