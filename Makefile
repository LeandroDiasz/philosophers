NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
THREAD = -pthread

SRC = src/init.c src/main.c src/parsing.c src/utils.c src/philo.c src/monitor.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(THREAD)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all