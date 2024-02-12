NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = functions.c pipex.c ft_strlen.c ft_split.c ft_strjoin.c ft_substr.c ft_strdup.c ft_strstr.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -fsanitize=address

# $(OBJS): $(SRCS)
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
