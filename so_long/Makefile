# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g3

# Source files
SRCS = main.c resource_cleanup.c map_loader.c animation_init.c map_validator.c\
		map_renderer.c graphics_utils.c player_controls.c  animation_utils.c

# Object files
OBJS= $(SRCS:.c=.o)

# libraries
LIBS= -lmlx -lXext -lX11 -lm -Llibft -lft

# Targets
NAME = so_long

# Rules
$(NAME): all

all: $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

clean:
	@make -C libft clean
	rm -rf $(OBJS)

fclean: clean
	@make -C libft fclean
	rm -rf $(NAME)

re: fclean all

# Object file rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: clean fclean re all bonus