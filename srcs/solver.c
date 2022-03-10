/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:56:41 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/10 14:55:08 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	fit_block(unsigned int *bb, t_tetri *tm, int y, int offset)
{
	int	i;

	i = 0;
	while (tm->bitfield[i] != 0 && i < 4)
	{
		if ((bb[y + i] & ((tm->bitfield[i] >> offset))) == 0)
			++i;
		else
			return (0);
	}
	return (1);
}

int	solve_it(unsigned int *bb, t_tetri **tm, int size)
{
	if ((*tm) == NULL)
		return (1);
	(*tm)->y = 0;
	if ((*tm)->prev_same != NULL)
		(*tm)->y = (*tm)->prev_same->y;
	while ((*tm)->y + (*tm)->height <= size)
	{
		(*tm)->x = 0;
		while ((*tm)->x + (*tm)->width <= size)
		{
			if ((bb[(*tm)->y] & ((*tm)->bitfield[0] >> (*tm)->x)) == 0
				&& fit_block(bb, *tm, (*tm)->y, (*tm)->x))
			{
				toggler(bb, *tm);
				if (solve_it(bb, tm + 1, size) == 1)
					return (1);
				toggler(bb, *tm);
			}
			++(*tm)->x;
		}
		++(*tm)->y;
	}
	(*tm)->x = 0;
	(*tm)->y = 0;
	return (0);
}
