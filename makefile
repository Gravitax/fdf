# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/25 15:11:15 by maboye            #+#    #+#              #
#    Updated: 2019/07/30 17:45:01 by maboye           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

HEADER	=	fdf.h

LIB		=	libft/libft.a

OBJ 	=	$(SRC:.c=.o)

SRC		=	bresenham.c \
			draw.c \
			draw2.c \
			event.c \
			fdf.c \
			ft_atoi_base.c \
			parsing.c \
			rotation.c \
			struct.c \
			utils.c \
			main.c

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror
#-g3 -fsanitize=address

MLX		=	-lmlx -framework OpenGL -framework AppKit -I /usr/local/include -L /usr/local/lib

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
			@$(CC) $(CFLAGS) $(INCL) $(MLX) $(LIB) $(OBJ) -o $@
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