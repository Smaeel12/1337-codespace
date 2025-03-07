NAME = pipex
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g3
SRCS = pipex.c pipex_utils.c resource_cleanup.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) -Llibft -lft

%.o: %.c
	make -C libft
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
