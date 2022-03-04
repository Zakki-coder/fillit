/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:08:35 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/04 12:03:40 by jniemine         ###   ########.fr       */
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
