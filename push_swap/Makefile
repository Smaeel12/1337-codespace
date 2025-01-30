NAME = push_swap
# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Source files
SRCS = args_parser.c helpers.c instructions.c
PUSH_SWAP_SRCS = $(SRCS) push_swap.c
CHECKER_SRCS = $(SRCS) checker.c instruction_bonus.c

# Object files
OBJS = $(SRCS:.c=.o)
PUSH_SWAP_OBJS = $(PUSH_SWAP_SRCS:.c=.o)
CHECKER_OBJS = $(CHECKER_SRCS:.c=.o)

# Libft directory and library
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Targets
NAME = push_swap
CHECKER = checker

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(PUSH_SWAP_OBJS)
	$(CC) $(CFLAGS) $^ -L$(LIBFT_DIR) -lft -o $@

bonus: $(LIBFT) $(CHECKER)

$(CHECKER): $(CHECKER_OBJS)
	$(CC) $(CFLAGS) $^ -L$(LIBFT_DIR) -lft -o $@

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean rules
clean:
	rm -f $(OBJS) $(PUSH_SWAP_OBJS) $(CHECKER_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(CHECKER)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Object file rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: clean fclean re all bonus

# Secondary targets
.SECONDARY: $(PUSH_SWAP_OBJS) $(CHECKER_OBJS)