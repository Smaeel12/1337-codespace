# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g3

# Source files
SRCS = so_long.c map_loader.c resource_cleanup.c game_init.c animation_init.c debug.c\
		#map_renderer.c graphics_utils.c player_controls.c  animation_utils.c map_validator.c

# Object files
OBJS= $(SRCS:.c=.o)

# libraries
# LIBS= -lmlx -lXext -lX11 -lm -Llibft -lft
LIBS= -Lmlx -lmlx -lXext -lX11 -lm -Llibft -lft
# Targets
NAME = so_long

# Rules
all: $(NAME)

$(NAME): $(OBJS)
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
