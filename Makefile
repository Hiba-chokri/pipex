NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = pipex.c functions.c  ft_strlen.c ft_split.c ft_strjoin.c ft_substr.c ft_strdup.c ft_strstr.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
