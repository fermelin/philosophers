

NAME = philo_one

SRC =	./srcs/main_ph1.c \
		./srcs/utils_ph1.c \
		./srcs/ft_atoi_ph1.c \
		./srcs/actions_ph1.c \
		./srcs/actions_utils_ph1.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I ./includes

.PHONY = all clean fclean re

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -lpthread
endif

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
		rm -f $(OBJ)
		rm -rf $(NAME).dSYM
		rm -f ./srcs/.DS_Store

fclean: clean
		rm -f $(NAME)

re: fclean all
