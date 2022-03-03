# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 13:06:54 by jniemine          #+#    #+#              #
#    Updated: 2022/03/03 17:23:22 by jniemine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CFLAG = -Wall -Wextra -Werror

INCLUDES = -I./ -I./libft/includes/

SRCS =	fillit.c			\
		libft/ft_putchar.c	\
		libft/ft_putstr.c	\
		libft/ft_memalloc.c	\
		libft/ft_bzero.c	\
		libft/ft_memset.c	\

OBJ =	fillit.o		\
		ft_putchar.o	\
		ft_putstr.o		\
		ft_memalloc.o	\
		ft_bzero.o		\
		ft_memset.o		\

all:
	@gcc -c ${SRCS} ${INCLUDES} 
	@gcc ${OBJ} -o ${NAME}

clean:
	@rm ${OBJ}

fclean: clean
	@rm ${NAME}

re: fclean all
