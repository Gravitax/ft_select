# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/25 15:11:15 by maboye            #+#    #+#              #
#    Updated: 2019/05/08 16:28:02 by maboye           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_select

HEADER	=	ft_select.h

LIB		=	libft/libft.a

SRC		=	display.c \
			dlst_functions.c \
			ft_select.c \
			move.c \
			signal_handler.c \
			terminal.c \
			utils.c

OBJ 	=	$(SRC:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror
#-g3 -fsanitize=address

INCL		=	-I .

BLACK	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
TUR		=	\033[36m
WHITE	=	\033[37m
END		=	\033[0m

UP 		=	\033[A
CUT 	=	\033[K

all:		$(NAME)

$(LIB):
			@$(MAKE) -C libft/
			@echo "${GREEN}[LIBRARY COMPILED]${END}"

%.o:		%.c
			@echo "${BLUE}compiling [$@] ...${END}"
			@$(CC) $(CFLAGS) $(INC) -c -o $@ $<
			@printf "$(UP)$(CUT)"

$(NAME):	$(LIB) $(OBJ) $(HEADER)
			@$(CC) $(CFLAGS) $(INCL) -ltermcap -lncurses $(LIB) $(OBJ) -o $@
			@echo "${GREEN}[$@ COMPILED]${END}"
clean:
			@/bin/rm -rf $(OBJ)
			@$(MAKE) -C libft/ clean
			@echo "${PURPLE}[.o deleted]${END}"

fclean:		clean
			@/bin/rm -rf $(NAME)
			@$(MAKE) -C libft/ fclean
			@echo "${RED}[$(NAME) deleted]${END}"
			@echo "${RED}[$(LIB) deleted]${END}"

re:			fclean all

.PHONY:		all clean fclean re
