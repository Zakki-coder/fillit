/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:52:13 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/14 10:17:39 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
