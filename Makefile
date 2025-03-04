NAME = philo

SRC = main.c threads.c utils.c cont_philo.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

all: $(NAME)

# $(NAME): $(OBJ)
# 	cc -g $(CFLAGS) -o $(NAME) $(OBJ)

$(NAME): $(OBJ)
	cc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all