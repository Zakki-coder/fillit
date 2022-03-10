/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:52:13 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/10 23:42:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetri	*reader(char *arr)
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

int	check_blocks(char *blocks, int bytes, int i)
{
	char	block[21];

	if (bytes > 26 * 21 - 1 || bytes % 21 != 20
		|| !has_seperating_nl(blocks, bytes))
		return (-1);
	while (bytes > 0)
	{
		while (i < 20)
		{
			if (!validate_char(blocks[i], bytes))
				return (-3);
			if (blocks[i] == '\n' && (i + 1) % 5 != 0
				|| (i + 1) % 5 == 0 && blocks[i] != '\n')
				return (-4);
			block[i] = blocks[i];
			++i;
			--bytes;
		}
		if (!touch_count(block))
			return (-5);
		i = 0;
		blocks += 21;
		--bytes;
	}
	return (1);
}

int	validate_char(char c, int bytes)
{
	return (c == '.' || c == '#' || c == '\n');
}

int	touch_count(char *block)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < 20)
	{
		if (block[i] == '#')
		{
			if (i / 5 > 0 && block[i - 5] == '#')
				++count;
			if (i / 5 < 3 && block[i + 5] == '#')
				++count;
			if (i % 5 > 0 && block[i - 1] == '#')
				++count;
			if (i % 5 < 3 && block[i + 1] == '#')
				++count;
		}
		++i;
	}
	return (count == 6 || count == 8);
}
