/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:28:13 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/04 13:16:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_tetrimino
{
	unsigned int	*bitfield;
	int				x;
	int				y;
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
	int				height;
	int				width;
	char			symbol;
}					t_tetri;

void			nullifier(t_tetri **tm, int i);
unsigned int	is_on(unsigned int bf, unsigned int n);
int				fit_first_ln(unsigned int bb, t_tetri *tm);
void			toggler(unsigned int *bb, t_tetri *tm);
unsigned int	flip_bit(unsigned int bf, unsigned int n);
t_tetri			*limits(char *arr, t_tetri *tetri);
void			char_to_bit(char *buff, int bytes, t_tetri **tetriminos);
int				check_blocks(char *blocks, int bytes, int i);
int				validate_char(char c, int bytes);
int				touch_count(char *block);
int				solve_it(unsigned int *bb, t_tetri **tm, int size);

#endif
