/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_wizardry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:42:41 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/10 23:40:57 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

unsigned int	is_on(unsigned int bf, unsigned int n)
{
	return (bf >> n & (unsigned int)1);
}

int	fit_first_ln(unsigned int bb, t_tetri *tm)
{
	if ((bb & (tm->bf[0] >> tm->x)) > 0)
		return (0);
	return (1);
}

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

unsigned int	flip_bit(unsigned int bf, unsigned int n)
{
	return (bf |= ((unsigned int)1 << n));
}
