/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:28:13 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/18 15:10:52 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_tetrimino	t_tetri;

struct s_tetrimino
{
	unsigned int	bf[4];
	int				x;
	int				y;
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
	int				height;
	int				width;
	char			symbol;
	t_tetri			*prev_same;
};

int				parse_input(char **argv, int argc, t_tetri **tm);
void			printer(int size, t_tetri **tm);
void			char_to_bit(char *buff, int bytes, t_tetri **tetriminos);
int				solve_it(unsigned int *bb, t_tetri **tm, int size, int i);

#endif
