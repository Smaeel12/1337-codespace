NAME        := app
CPP         := c++ --std=c++98
CFLAGS      := -W -Wextra -Werror
SRCS        := Bureaucrat
INCLUDES    := ${SRCS:%=%.hpp}
OBJS        := objs/main.o $(SRCS:%=objs/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) $^ -o $@

objs/%.o: %.cpp $(INCLUDES)
	@mkdir -p objs/
	$(CPP) $(CFLAGS) -c $< -o $@

clean:
	rm -rf objs/

fclean: clean
	rm -rf $(NAME)

re: fclean all

