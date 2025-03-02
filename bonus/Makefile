NAME = philo_bonus

SRC = main_bonus.c threads_bonus.c time_bonus.c utils_bonus.c 

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

# $(NAME): $(OBJ)
# 	cc -g $(CFLAGS) -o $(NAME) $(OBJ)

$(NAME): $(OBJ)
	cc $(CFLAGS) -g -o $(NAME) $(OBJ) -pthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all