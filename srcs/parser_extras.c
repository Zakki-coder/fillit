/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:08:35 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/10 23:41:26 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetri	*limits(char *arr, t_tetri *tetri)
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

int	has_seperating_nl(char *blocks, int bytes)
{
	int	i;

	i = 0;
	while (i < bytes)
	{
		if ((i + 1) % 21 == 0 && blocks[i] != '\n')
			return (0);
		++i;
	}
	return (1);
}

int	compare_bitfields(unsigned int *bf1, unsigned int *bf2)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (bf1[i] != bf2[i])
			return (0);
		++i;
	}
	return (1);
}

void	search_similar(t_tetri **tm)
{
	int	i_tm;
	int	i;

	i_tm = 0;
	i = 0;
	while (tm[i] != NULL)
		tm[i++]->prev_same = NULL;
	while (tm[i_tm] != NULL)
	{
		i = 0;
		while (i_tm > 0 && i < i_tm)
		{
			if (compare_bitfields(tm[i_tm]->bf, tm[i]->bf))
			{
				tm[i_tm]->prev_same = tm[i];
				break ;
			}
			++i;
		}
		++i_tm;
	}
}
