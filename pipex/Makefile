NAME = pipex

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g3

SRCS = main.c extract_cmds.c #close_program.c
OBJS = $(SRCS:.c=.o)

LIBS = -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

all: $(NAME)

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

#	make re -C libft

.PHONY: all clean fclean re