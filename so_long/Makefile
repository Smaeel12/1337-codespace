# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS= main.c game_setup.c error_handler.c resource_cleanup.c player_controls.c \
	graphics_utils.c map_validator.c map_loader.c map_renderer.c

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