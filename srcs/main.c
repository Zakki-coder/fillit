/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:01:58 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/10 13:38:53 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
			if (is_on((*tm)->bitfield[i / 4], 31 - (i % 4)))
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
	while (solve_it(bit_board, tetriminos, size) != 1)
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
