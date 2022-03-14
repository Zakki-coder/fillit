/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:32:03 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/14 10:32:18 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

unsigned int	is_on(unsigned int bf, unsigned int n)
{
	return (bf >> n & (unsigned int)1);
}

char	*create_array(int size)
{
	char	*board;
	int		i;

	i = 0;
	board = (char *)ft_memalloc(sizeof(*board) * (size * size) + size + 1);
	if (board == NULL)
		exit(-1);
	ft_bzero(board, sizeof(*board) * size * size + size);
	ft_memset(board, '.', sizeof(*board) * size * size + size);
	while (i * (size + 1) < size * size + size)
	{
		board[i * (size + 1) + (size)] = '\n';
		++i;
	}
	return (board);
}

void	printer(int size, t_tetri **tm)
{
	int		i;
	int		start;
	char	*board;

	board = create_array(size);
	i = 0;
	while (*tm != NULL)
	{
		start = (*tm)->y * (size + 1) + (*tm)->x;
		while (i / 4 < (*tm)->height)
		{
			if (is_on((*tm)->bf[i / 4], 31 - (i % 4)))
				board[start + (i / 4 * (size + 1)) + (i % 4)] = (*tm)->symbol;
			++i;
		}
		i = 0;
		++tm;
	}
	ft_putstr(board);
	free(board);
	return ;
}

void	free_tetri(t_tetri **tm)
{
	while ((*tm) != NULL)
	{
		free((*tm));
		++tm;
	}
	return ;
}
