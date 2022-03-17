/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:52:13 by jniemine          #+#    #+#             */
/*   Updated: 2022/03/17 07:41:19 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	has_seperating_nl(char *blocks, int bytes)
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

static int	validate_char(char c)
{
	return (c == '.' || c == '#' || c == '\n');
}

static int	touch_count(char *block, int hash_nb)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < 20)
	{
		if (block[i] == '#')
		{
			++hash_nb;
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
	return ((count == 6 || count == 8) && hash_nb == 4);
}

static int	check_blocks(char *blocks, int bytes, int i)
{
	char	block[21];

	if (bytes > 26 * 21 - 1 || bytes % 21 != 20
		|| !has_seperating_nl(blocks, bytes))
		return (-1);
	while (bytes > 0)
	{
		while (i < 20)
		{
			if (!validate_char(blocks[i]))
				return (-3);
			if ((blocks[i] == '\n' && (i + 1) % 5 != 0)
				|| ((i + 1) % 5 == 0 && blocks[i] != '\n'))
				return (-4);
			block[i] = blocks[i];
			++i;
			--bytes;
		}
		if (!touch_count(block, 0))
			return (-5);
		i = 0;
		blocks += 21;
		--bytes;
	}
	return (1);
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
