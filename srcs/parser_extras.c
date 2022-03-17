/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:08:35 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/17 07:42:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_tetri	*limits(char *arr, t_tetri *tetri)
{
	int	i;

	i = 0;
	tetri->x_min = 3;
	tetri->x_max = 0;
	tetri->y_min = 3;
	tetri->y_max = 0;
	while (i < 20)
	{
		if (arr[i] == '#')
		{
			if (i % 5 < tetri->x_min)
				tetri->x_min = i % 5;
			if (i % 5 > tetri->x_max)
				tetri->x_max = i % 5;
			if (i / 5 < tetri->y_min)
				tetri->y_min = i / 5;
			if (i / 5 > tetri->y_max)
				tetri->y_max = i / 5;
		}
		++i;
	}
	return (tetri);
}

static unsigned int	flip_bit(unsigned int bf, unsigned int n)
{
	return (bf |= ((unsigned int)1 << n));
}

static t_tetri	*reader(char *arr)
{
	t_tetri			*tetri;
	int				i;
	int				row;
	int				column;

	tetri = (t_tetri *)ft_memalloc(sizeof(*tetri));
	if (!tetri)
		exit(-1);
	i = 0;
	tetri = limits(arr, tetri);
	tetri->width = tetri->x_max - tetri->x_min + 1;
	tetri->height = tetri->y_max - tetri->y_min + 1;
	while (i < 20)
	{
		row = i / 5;
		column = i % 5;
		if (arr[i] == '#')
			tetri->bf[row - tetri->y_min]
				|= flip_bit(0, 31 - (column - tetri->x_min));
		++i;
	}
	return (tetri);
}

void	char_to_bit(char *buff, int bytes, t_tetri **tetriminos)
{
	char	block[21];
	char	sym;
	int		i;
	t_tetri	**tt;

	ft_bzero(block, 21);
	sym = 'A';
	tt = tetriminos;
	i = 0;
	bytes = bytes - bytes / 21 + 1;
	while (bytes--)
	{
		block[i] = buff[i];
		++i;
		if (i == 20)
		{
			*tt = reader(block);
			(*tt)->symbol = sym++;
			tt++;
			i = 0;
			buff += 21;
		}
	}
	return ;
}
