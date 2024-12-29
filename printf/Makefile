NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c
BONUS = ft_printf_bonus.c
OBJS = $(SRCS:.c=.o)
BOBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

bonus: $(OBJS) $(BOBJS)
	ar rcs $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJS) $(BOBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus

.SECONDARY: $(OBJS) $(BOBJS)