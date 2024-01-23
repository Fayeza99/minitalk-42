COLOUR_GREEN = \033[0;32m
COLOUR_RED = \033[0;31m
COLOUR_BLUE = \033[0;34m
COLOUR_END = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = server.c client.c
OBJ = $(SRC:.c=.o)

SERVER_NAME = server
CLIENT_NAME = client


all:	$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) server.o -o $(SERVER_NAME)

$(CLIENT_NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) client.o -o $(CLIENT_NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

re:	fclean all

.PHONY:	all clean fclean re