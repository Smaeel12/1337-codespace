NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3 #-fsanitize=thread
SRCS = main.c utils.c philosopher.c
OBJS = $(addprefix objs/, $(SRCS:.c=.o))
HEADER = main.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

objs/%.o: %.c $(HEADER)
	@mkdir -p objs/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf objs/

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re