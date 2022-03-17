# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 13:06:54 by jniemine          #+#    #+#              #
#    Updated: 2022/03/14 14:23:36 by jniemine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CFLAG = -Wall -Wextra -Werror

INCLUDES =	-I./srcs/			\
			-I./libft/includes/

SRCS =	srcs/parser_extras.c\
		srcs/main.c			\
		srcs/main_extra.c	\
		srcs/parser.c		\
		srcs/solver.c		\
		libft/ft_putchar.c	\
		libft/ft_putstr.c	\
		libft/ft_memalloc.c	\
		libft/ft_bzero.c	\
		libft/ft_memset.c	\

OBJ =	parser_extras.o	\
		main.o			\
		main_extra.o	\
		parser.o		\
		solver.o		\
		ft_putchar.o	\
		ft_putstr.o		\
		ft_memalloc.o	\
		ft_bzero.o		\
		ft_memset.o		\

$(NAME):
	@gcc -c ${CFLAG} ${SRCS} ${INCLUDES} 
	@gcc ${OBJ} -o ${NAME}

all: $(NAME)

clean:
	@rm -f ${OBJ}

fclean: clean
	@rm -f ${NAME}

re: fclean all
