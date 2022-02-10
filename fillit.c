#include <stdio.h>//DELTDELT
#include <unistd.h>
#include "fillit.h"

void print_bit(unsigned int *bit_board, int size)
{
	int i = 0;
	int x = 0;
	while (i < size)
	{
		while (x < size)
		{
			if (bit_board[i] & (((unsigned int)1 << (31 - x))))
				ft_putchar('1');
			else
				ft_putchar('0');
			++x;
		}
		x = 0;
		ft_putchar('\n');
		++i;
	}
	ft_putchar('\n');
	return ;
}

unsigned int flip_bit(unsigned int bf, unsigned int n)
{
	return(bf |= ((unsigned int)1 << n));
}

unsigned int is_on(unsigned int bf, unsigned int n)
{
	return(bf >> n & (unsigned int)1);
}

void printer(unsigned int *board, int size)
{
	int i;
	int i_bf;
	int line;

	i_bf = 1;
	i = 0;
	line = board[i / size];
	while (i < 20)
	{
		++i;
		if (i % (size + 1) == 0)
		{
			line = board[i / size];
			i_bf = 1;
			if (i > 1 && i % (size + 1) == 0)
				ft_putchar('\n');
			continue ;
		}
		if (is_on(line, 32 - i_bf))
			ft_putchar('X');
		else if (i % (size + 1) != 0)
			ft_putchar('.');
		if (i % (size + 1) != 0)
			++i_bf;
	}
	return ;
}

unsigned int get_bit_line(unsigned int bf, int ln, int ln_len)
{
	bf = bf << (ln * ln_len);
	bf = bf >> (32 - ln_len);
	bf = bf << (32 - ln_len);

	return (bf);
}
/*
void	write_bit_board(unsigned int *board, t_tetri **tetriminos, int size)
{
	int				i;
	unsigned int	res;
	unsigned int	bf;

 	i = 0;
	while (*tetriminos != NULL)
	{
		bf = *((*tetriminos)->bitfield);
		while (i <= 16)
		{
			if (i % 4 == 0)
			{
				res = get_bit_line(bf, i / 4, 4);
				if (res == 0)
					break ;
				board[i / 4] = res;
			}
			++i;
		}
		i = 0;
		printer(board, 4);
		while(i < 16)
			board[i++] = 0;
		i = 0;
		printf("\n");
		++tetriminos;
	}
	return ;
}
*/
t_tetri	*limits(char *arr, t_tetri *tetri)
{
	int i;

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

t_tetri *reader(char *arr)
{
	t_tetri			*tetri;
	int				i;

	tetri = (t_tetri *)ft_memalloc(sizeof(*tetri));
	if (!tetri)
		_exit(-1);
	i = 0;
	tetri = limits(arr, tetri);
	tetri->width = tetri->x_max - tetri->x_min + 1;
	tetri->height = tetri->y_max - tetri->y_min + 1;
	tetri->bitfield = ft_memalloc(sizeof(unsigned int) * 4);
	tetri->x = -1;
	tetri->y = -1;
	if (tetri->bitfield == NULL)
		_exit(-1);
	while (i < 20)
	{
		if(arr[i] == '#')
			tetri->bitfield[(i / 5) - tetri->y_min] |= flip_bit(0, 31 - ((i % 5) - tetri->x_min));
		++i;
	}
	return (tetri);
}

void	char_to_bit(char *buff, int bytes, t_tetri **tetriminos)
{
	char block[21] = {'\0'};
	char sym;
	int i;
	t_tetri	**tt;

	sym = 'A';
	tt = tetriminos;
	i = 0;
	bytes = bytes - bytes / 21 + 1;
	while (bytes--)
	{
		block[i] = buff[i];
		++i;
		if (i == 20)
		{
			*tt = reader(block);
			(*tt)->symbol = sym++;
			tt++;
			i = 0;
			buff += 21;
		}
	}
	return ;
}

int validate_char(char c, int bytes)
{
	return(c == '.' || c == '#' || c == '\n' || (bytes == 0 && c == '\0'));
}

int is_hash(char c)
{
	return (c == '#');
}

int touch_count(char *block)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (i < 20)
	{
		if (block[i] == '#')
		{
			if (i / 5 > 0 && is_hash(block[i - 5]))
				++count;
			if (i / 5 < 3 && is_hash(block[i + 5]))
				++count;
			if (i % 5 > 0 && is_hash(block[i - 1]))
				++count;
			if (i % 5 < 3 && is_hash(block[i + 1]))
				++count;
		}
		++i;
	}
	return (count == 6 || count == 8);
}
//Correct block/line always ends with \n fix it.				
int check_blocks(char *blocks, int bytes)
{
	int i;
	char block[21];

	i = 0;
	//If number of blocks is larger than 26 or if size of last block differs from 20
	if (bytes > 26 * 21 - 1 || bytes % 21 != 20)
		return (-1);
	while (bytes > 0)
	{
		while(i < 20)
		{
			if (!validate_char(blocks[i], bytes))
			{
				return (-2);
			}
			if ((((i + 1) % 5 == 0 && blocks[i] != '\n')
			|| (((i + 1) % 5 != 0) && blocks[i] == '\n')))
			{	
				return (-3);
			}
			block[i] = blocks[i];
			++i;
			--bytes;
		}
		if (!touch_count(block))
			return (-4);
		i = 0;
		blocks += 21;
		--bytes;
	}
	return (1);
}

//function to test rest of lines
int fit_line(unsigned int bb, unsigned int tm, int offset)
{
	return (bb & tm >> offset);
}
/* Call solve_it recursively for all tetriminos, if NULL is reached, then all tetriminos fit
 * TODO: If all possible places have been tried, return 0 for failure
 */
int solve_it(unsigned int *bb, t_tetri **tm, int size)
{
	int i;
	unsigned int first_ln;

	if ((*tm) == NULL)
		return (1);
	first_ln = *(*tm)->bitfield >> (++(*tm)->x);
	printf("first_ln: %u\t", first_ln);
	i = 0;
	printf ("height: %d\n", (*tm)->height);
	printf("i: %d\n", i);
	print_bit((*tm)->bitfield, 4);
	//bb[0] = 0b10100000000000000000000000000000;
	//Find a place for first line of tetrimino block
	while (i < size && (bb[i] & first_ln) > 0)
	{
		printf("x: %d\n", (*tm)->x);
		if ((*tm)->x + (*tm)->width < size)
		{
			++(*tm)->x;
			first_ln = first_ln >> (unsigned int)1;
		}
		else
		{
			first_ln = *tm[0]->bitfield;
			(*tm)->x = 0;
			++i;
		}
	}
//Check if rest of tetrimino lines fit
//	printf("x: %d\n", (*tm)->x);
	int tm_i;

	tm_i = 1;
	(*tm)->y = i;
	++i;
	while (i < size && (*tm)->bitfield[tm_i] > 0 && !fit_line(bb[i++], (*tm)->bitfield[tm_i++], (*tm)->x))
		;
	printf("tm_i: %d\n", tm_i);
	if (tm_i == (*tm)->height)
	{	
		while(tm_i >= 0)
		{
			bb[--i] |= ((*tm)->bitfield[--tm_i] >> (*tm)->x);
		}
		//If this block fits, call function for next block
		if (solve_it(bb, tm + 1, size))
		{
			return (1);
		}
/*		else
		{
			if (solve_it(bb, tm, size)
				return (1);
			return (0);
		}
*/	}
	//Check if block could be moved and if so then call function for same block
	if ((((*tm)->y - 1) * size + ((*tm)->x + (*tm)->width) < size * size))
	{
		//If this block doesn't fit, call function for this block again.
		if(solve_it(bb, tm, size))
			return 1;
	}
	return (0);
}

int main(int argc, char **argv)
{
	char			buff[26 * 21 + 1] = {'\0'};
	unsigned int	bit_board[16] = {0};
	t_tetri			*tetriminos[26 + 1] = {NULL};
	int bytes;
	int fd;
	int i;
	int size;
	
	i = 0;
	if(argc != 2)
	{
		ft_putstr("Usage: ./fillit [argument]");	
		return (0);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		bytes = read(fd, buff, 26 * 21);
		int res = 0;
		if ((res = check_blocks(buff, bytes)) != 1)
		{
			printf("Res: %d\n", res);
			return (-1);
			}
	}
	char_to_bit(buff, bytes, tetriminos);
	size = 4;
	while(solve_it(bit_board, tetriminos, size) != 1)
	{
		printf("trastui\n");
		++size;
		while(i < 16)
			bit_board[i++] = 0;
		i = 0;
		while (tetriminos[i] != NULL)
		{
			tetriminos[i]->x = -1;
			tetriminos[i]->y = -1;
			++i;
		}
	}
	print_bit(bit_board, size);
	return(0);
}
