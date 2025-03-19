# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = main.c resource_cleanup.c map_loader.c animation_init.c map_validator.c\
		map_renderer.c graphics_utils.c player_controls.c  animation_utils.c\
		error_strings.c render_utils.c

# Object files
OBJS= $(addprefix objs/, $(SRCS:.c=.o))
BOBJS= $(addprefix bobjs/, $(SRCS:.c=.o))

# libraries
LIBS= -Lmlx -lmlx -lXext -lX11 -lm -Llibft -lft

# Targets
NAME = so_long

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

bonus: $(BOBJS)
	@make -C libft
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

clean:
	@make -C libft clean
	rm -rf objs bobjs

fclean: clean
	@make -C libft fclean
	rm -rf $(NAME)

re: fclean all

# Object file rule
objs/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Bonus object file rule
bobjs/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -D BONUS_MODE=1 -c $< -o $@

# Phony targets
.PHONY: clean fclean re all bonus
