# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/21 17:30:58 by fermelin          #+#    #+#              #
#    Updated: 2021/01/04 20:22:10 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SONAME = libft.so

SRC_MAIN = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJ_MAIN = $(SRC_MAIN:.c=.o)

SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c \
			get_next_line.c ft_isspace.c ft_strjoin_free.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)
			
all: $(NAME)

ifdef WITH_BONUS
SRC = $(SRC_MAIN) $(SRC_BONUS)
OBJ = $(OBJ_MAIN) $(OBJ_BONUS)
else
SRC = $(SRC_MAIN)
OBJ = $(OBJ_MAIN)
endif

$(NAME): $(OBJ)
		ar rc $(NAME) $?
		ranlib $(NAME)

%.o: %.c
		gcc -Wall -Wextra -Werror -c $< -o $@

bonus:
		$(MAKE) WITH_BONUS=1 all

so:
		clang -shared -o $(SONAME) -fPIC $(SRC) $(SRC_BONUS)

clean:
		rm -f $(OBJ_MAIN) $(OBJ_BONUS)

fclean: clean
		rm -f $(NAME) $(SONAME)

re: fclean all

.PHONY = all bonus so clean fclean re