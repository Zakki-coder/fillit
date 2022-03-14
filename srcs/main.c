/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:01:58 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/14 10:04:02 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	nullifier(t_tetri **tm, int i)
{
	while (i)
	{
		--i;
		tm[i] = NULL;
	}
}

int	parse_input(char **argv, int argc, t_tetri **tm)
{
	int		fd;
	int		bytes;
	char	buff[26 * 21 + 1];

	ft_bzero(buff, 26 * 21 + 1);
	if (argc != 2)
	{
		ft_putstr("Usage: ./fillit argument\n");
		exit (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("error\n");
		exit (-1);
	}
	bytes = read(fd, buff, 26 * 21);
	if (bytes < 0 || check_blocks(buff, bytes, 0) != 1)
	{
		ft_putstr("error\n");
		exit (-1);
	}
	close (fd);
	char_to_bit(buff, bytes, tm);
	return (bytes / 21 + 1);
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

int	main(int argc, char **argv)
{
	unsigned int	bit_board[16];
	t_tetri			*tetriminos[26 + 1];
	int				i;
	int				size;
	int				block_n;

	nullifier(tetriminos, 27);
	ft_bzero(bit_board, 16);
	block_n = parse_input(argv, argc, tetriminos);
	search_similar(tetriminos);
	size = 2;
	while (size * size < block_n * 4)
		++size;
	while (solve_it(bit_board, tetriminos, size, 0) != 1)
	{
		i = 0;
		++size;
		while (i < 16)
			bit_board[i++] = 0;
	}
	printer(size, tetriminos);
	free_tetri(tetriminos);
	return (0);
}
