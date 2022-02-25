#include <unistd.h>
#include "fillit.h"

unsigned int flip_bit(unsigned int bf, unsigned int n)
{
	return(bf |= ((unsigned int)1 << n));
}

unsigned int is_on(unsigned int bf, unsigned int n)
{
	return(bf >> n & (unsigned int)1);
}

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
	tetri->x = 0;
	tetri->y = 0;
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

//Last condition? Maybe not needed anymore.
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

int can_it_move(unsigned int *bf, int size, int x)
{
	unsigned int	one;
	int 			i;

	one = 1;
	i = 0;
	while (bf[i] != 0 && i < 4)
	{
		if (((bf[i] >> (x + 1)) & (one << (31 - size))) > 0)
			return (0);	
		++i;
	}
	return (1);
}

int fit_block(unsigned int *bb, t_tetri *tm, int y, int offset)
{
	int i;

	i = 0;
	while (tm->bitfield[i] != 0 && i < 4)
	{
		if((bb[y + i] & ((tm->bitfield[i] >> offset))) == 0)
			++i;
		else
			return (0);
	}
	return (1);
}
	
int find_place(unsigned int *bb, t_tetri *tm, int size)
{
	int x;
	int y;

	x = tm->x;
	y = tm->y;
	if (tm->width > size)
		return (0);
	while (y + tm->height <= size && !fit_block(bb, tm, y, x))
	{
			if (can_it_move(tm->bitfield, size, x))	
				++x;
			else
			{
				++y;
				x = 0;
			}
	}
	if (y + tm->height > size)
		return (0);
	tm->x = x;
	tm->y = y;
	return (1);
}

int solve_it(unsigned int *bit_board, t_tetri **tetriminos, int size)
{
	unsigned int bb[16] = {0};
	t_tetri **tm;

	ft_memcpy(bb, bit_board, sizeof(*bb) * 16);
	tm = tetriminos;
	if ((*tm) == NULL)
		return (1);
	int res;
	int res2;

	res2 = 0;
	res = 0;
	int i = 0;
	if (!find_place(bb, *tm, size))
		{
			return ((*tm)->symbol);
		}
		while(i < (*tm)->height)
		{
			bb[(*tm)->y + i] |= ((*tm)->bitfield[i] >> (*tm)->x);
			++i;
		}
		res = solve_it(bb, tm + 1, size);
		if (res == 1)
			return (res);
		else if(can_it_move((*tm)->bitfield, size, (*tm)->x) || (*tm)->y + (*tm)->height < size)
		{
			if (can_it_move((*tm)->bitfield, size, (*tm)->x))
				++(*tm)->x;
			else if ((*tm)->y + (*tm)->height < size)
			{
				(*tm)->x = 0;
				++(*tm)->y;
			}
			res2 = solve_it(bit_board, tm, size);
		}
	if (res2 == 1)
		return (res2);
	(*tm)->x = 0;
	(*tm)->y = 0;
	return (res);
}

char *creat_array(int size)
{
	char *board;
	int i;

	i = 0;
	board = (char *)ft_memalloc(sizeof(*board) * (size * size) + size + 1);
	if (board == NULL)
		_exit(-1);
	ft_bzero(board, sizeof(*board) * size * size + size);
	ft_memset(board, '.', sizeof(*board) * size * size + size);
	while (i * (size + 1) < size * size + size)
	{
		board[i * (size + 1) + (size)] = '\n';
		++i;
	}
	return (board);
}

void printer(int size, t_tetri **tm)
{
	int i;
	int start;
	char *board;

	board = creat_array(size);
	i = 0;
	while (*tm != NULL)
	{
		start = (*tm)->y * (size + 1) + (*tm)->x;
		while (i / 4 < (*tm)->height)
		{
			if (is_on((*tm)->bitfield[i / 4], 31 - (i % 4)))
				board[start + (i/ 4 * (size + 1)) + (i % 4)] = (*tm)->symbol;
			++i;
		}
		i = 0;
		++tm;
	}
	ft_putstr(board);
	free(board);
	return ;
}
			
void free_tetri(t_tetri **tm)
{
	while ((*tm) != NULL)
	{
		free((*tm)->bitfield);
		free((*tm));
		++tm;
	}
	return ;
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
	int block_n;
	int res;

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
			return (-1);
	}
	char_to_bit(buff, bytes, tetriminos);

	i = 0;
	res = 0;
	block_n = bytes / 21 + 1;
	size = 2;
	while (size * size < block_n * 4)
		++size;
	while(res != 1)
	{
		res = solve_it(bit_board, tetriminos, size);  
		if(res == 1)
			break ;
		++size;
		while(i < 16)
			bit_board[i++] = 0;
		i = 0;
		while (tetriminos[i] != NULL)
		{
			tetriminos[i]->x = 0;
			tetriminos[i]->y = 0;
			++i;
		}
	}
	printer(size, tetriminos);
	free_tetri(tetriminos);	
	return(0);
}
