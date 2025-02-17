NAME = pipex

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

SRCS = main.c
OBJS = $(SRCS:.c=.o)

LIBS = -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

#	make re -C libft

.PHONY: all clean fclean re