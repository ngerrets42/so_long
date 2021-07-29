# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ngerrets <ngerrets@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/08 20:55:44 by ngerrets      #+#    #+#                  #
#    Updated: 2021/07/29 17:42:42 by ngerrets      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
CC = gcc -Werror -Wall -Wextra
SRC_CORE = get_next_line.c get_next_line_utils.c
OBJ_CORE = $(SRC_CORE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_CORE)
	@ar -r $(NAME) $(OBJ_CORE)

%.o: %.c
	$(CC) -c -o $@ $<

fclean:
	@rm -f $(OBJ_CORE)$(NAME)

re: fclean all

clean:
	@rm -f $(OBJ_CORE)

.PHONY: all clean fclean re
