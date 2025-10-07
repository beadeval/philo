NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  parse.c \
	  utils_parse.c \
	  get_time.c \
	  inits.c \
	  philo.c \
	  print.c \
	  routine.c \
	  philo_routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
