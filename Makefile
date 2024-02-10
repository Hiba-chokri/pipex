CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex.a
SRCS = functions.c pipex.c ft_strlen.c ft_split.c ft_strjoin.c ft_strncmp.c ft_substr.c ft_strdup.c 
OBJS = $(SRCS:.c=.o)
#special target
all: $(NAME)#default target, it is the first target in the file
#target rules : target files to be built(object files), along with the files they depend on(source files), and commands to build them
${OBJS}:${SRCS}
	${CC} ${CFLAGS} -c $^ 
#automatic variables, $^ is the source files, $@ is the target files

$(NAME):$(OBJS)
	ar rc $(NAME) $(OBJS)

clean: 
	rm -f $(OBJS) ${OBJF}

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus fclean clean re