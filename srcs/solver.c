/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:56:41 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/14 10:37:46 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	toggler(unsigned int *bb, t_tetri *tm)
{
	int	i;

	i = 0;
	while (i < tm->height)
	{
		bb[tm->y + i] ^= (tm->bf[i] >> tm->x);
		++i;
	}
}

int	solve_it(unsigned int *bb, t_tetri **tm, int size, int i)
{
	if ((*tm) == NULL)
		return (1);
	(*tm)->y = -1;
	if ((*tm)->prev_same != NULL)
		(*tm)->y = (*tm)->prev_same->y - 1;
	while (++(*tm)->y + (*tm)->height <= size)
	{
		(*tm)->x = -1;
		while (++(*tm)->x + (*tm)->width <= size)
		{
			i = 0;
			if ((bb[(*tm)->y] & ((*tm)->bf[0] >> (*tm)->x)) == 0 && ++i > 0)
				while (i < (*tm)->height && (bb[(*tm)->y + i]
						& ((*tm)->bf[i] >> (*tm)->x)) == 0)
					++i;
			if (i != (*tm)->height)
				continue ;
			toggler(bb, *tm);
			if (solve_it(bb, tm + 1, size, 0) == 1)
				return (1);
			toggler(bb, *tm);
		}
	}
	return (0);
}
