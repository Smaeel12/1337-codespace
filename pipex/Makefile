NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = pipex_utils.c resource_handler.c
OBJS = $(addprefix objs/, $(SRCS:.c=.o) pipex.o)
BOBJS = $(addprefix objs/, $(SRCS:.c=.o) pipex_bonus.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $^ -o $(NAME) -Llibft -lft

bonus: $(BOBJS)
	make -C libft
	$(CC) $(CFLAGS) $^ -o $(NAME) -Llibft -lft

objs/%.o: %.c
	@mkdir -p objs
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	make clean -C libft
	rm -rf objs/

fclean: clean
	make fclean -C libft
	rm -rf objs/

re: fclean all

.PHONY: all clean fclean re
