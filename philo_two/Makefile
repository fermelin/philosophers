# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 22:12:45 by fermelin          #+#    #+#              #
#    Updated: 2021/03/18 21:15:57 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

SRC =	./srcs/main_philo_two.c \
		./srcs/utils_philo_two.c \
		./srcs/utils2_philo_two.c \
		./srcs/actions_philo_two.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I ./includes

.PHONY = all clean fclean re

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
