NAME = pipex
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g3
SRCS = pipex_utils.c resource_handler.c
OBJS = $(SRCS:.c=.o) pipex.o
BOBJS = $(SRCS:.c=.o) pipex_bonus.o

all: $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $^ -o $(NAME) -Llibft -lft

bonus: $(BOBJS)
	make -C libft
	$(CC) $(CFLAGS) $^ -o $(NAME) -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	make clean -C libft
	rm -rf $(SRCS:.c=.o) pipex.o pipex_bonus.o

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all
