# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/21 17:30:58 by fermelin          #+#    #+#              #
#    Updated: 2021/03/16 19:16:55 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

SRC =	./srcs/philo_one.c \
		./srcs/utils_philo_one.c \
		./srcs/actions_philo_one.c

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

fclean: clean
		rm -f $(NAME)

re: fclean all
