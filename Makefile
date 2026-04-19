##
## EPITECH PROJECT, 2026
## C-Chatter
## File description:
## Makefile
##

CC          = clang
CFLAGS      = -Wall -Wextra -I./include

SERVER_SRC  = src/server/main.c \
              src/server/init.c \
              src/server/events.c \
              src/server/client_mgmt.c \
              src/server/packet_parser.c

CLIENT_SRC  = src/client/main.c

SERVER_OBJ  = $(SERVER_SRC:.c=.o)
CLIENT_OBJ  = $(CLIENT_SRC:.c=.o)

SERVER_NAME = chat_server
CLIENT_NAME = chat_client

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) -o $(SERVER_NAME) $(SERVER_OBJ) $(CFLAGS)

$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJ) $(CFLAGS)

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re
