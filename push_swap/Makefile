NAME = push_swap
CHECKER = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = args_parser.c helpers.c instructions.c minilibft.c
PUSH_SWAP_SRCS = $(SRCS) push_swap.c
CHECKER_SRCS = $(SRCS) checker.c instruction_bonus.c get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
PUSH_SWAP_OBJS = $(PUSH_SWAP_SRCS:.c=.o)
CHECKER_OBJS = $(CHECKER_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(PUSH_SWAP_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

bonus: $(CHECKER_OBJS)
	$(CC) $(CFLAGS) $^ -o $(CHECKER)

clean:
	rm -f $(OBJS) $(PUSH_SWAP_OBJS) $(CHECKER_OBJS)

fclean: clean
	rm -f $(NAME) $(CHECKER)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean fclean re all bonus

.SECONDARY: $(PUSH_SWAP_OBJS) $(CHECKER_OBJS)
