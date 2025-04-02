NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = $(addprefix srcs/, main.c utils.c) #$(wildcard srcs/*)
OBJS = $(addprefix objs/, $(SRCS:srcs/%.c=%.o))
HEADER = includes/main.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -pthread

objs/%.o: srcs/%.c $(HEADER)
	@mkdir -p objs/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf objs

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
