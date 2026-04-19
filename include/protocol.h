/*
** EPITECH PROJECT, 2026
** C-Chatter
** File description:
** protocol.h
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_

    #include <stdint.h>

    #define MAX_NAME_LENGTH 32
    #define MAX_MSG_LENGTH 512

    typedef enum packet_type_e {
        LOGIN_REQ = 1,
        MSG_REQ = 2,
        MSG_BRDCAST = 3
    } packet_type_t;

    typedef struct packet_header_s {
        uint16_t type;
        uint32_t length;
    } packet_header_t;

    typedef struct msg_payload_s {
        char sender[MAX_NAME_LENGTH];
        char text[MAX_MSG_LENGTH];
    } msg_payload_t;

#endif /* !PROTOCOL_H_ */
