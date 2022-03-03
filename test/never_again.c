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
/*
unsigned int get_bit_line(unsigned int bf, int ln, int ln_len)
{
	bf = bf << (ln * ln_len);
	bf = bf >> (32 - ln_len);
	bf = bf << (32 - ln_len);

	return (bf);
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

//function to test rest of lines
int fit_line(unsigned int bb, unsigned int tm, int offset)
{
	return (bb & tm >> offset);
}
/*
int  offset_calc(t_tetri *tm)
{
	int offset;
	int i;
	int x;

	x = 0;
	offset = 0;
	i = 0;
	while (!is_on(tm->bitfield[i], 31 - x))
		++x;
	if (x > offset)
		offset = x;
	++i;
	return (offset);
}
*/
/* Call solve_it recursively for all tetriminos, if NULL is reached, then all tetriminos fit
 * TODO: If all possible places have been tried, return 0 for failure
 */
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
//	int i;
//	unsigned int first_ln;
	unsigned int bb[16] = {0};
	t_tetri **tm;

//	print_bit(bit_board, size);
	ft_memcpy(bb, bit_board, sizeof(*bb) * 16);
	tm = tetriminos;
	if ((*tm) == NULL)
	{
//		print_bit(bit_board, size);
		return (1);
	}
/*	if (*(*tm)->x + (*tm)->width < size*(can_it_move(**tm, size)))
	{
//		printf("Triggerd\n");
		++(*tm)->x;
	}
	else if ((*tm)->width <= size && (*tm)->y + (*tm)->height < size)
	{
//		printf("here\n");
		++(*tm)->y;
		(*tm)->x = 0;//CHANGED THIS FROM 0
	}
*///	first_ln = (*tm)->bitfield[0] >> (*tm)->x;
//	i = 0;
	//Find a place for first line of tetrimino block
//	printf("X: %d, y: %d\n", (*tm)->x, (*tm)->y);
/*	while ((*tm)->y + (*tm)->height <= size && (bb[(*tm)->y] & first_ln) > 0)
	{
		printf("EMT\n");
		if (*(*tm)->x + (*tm)->width*(can_it_move(**tm, size)))
		{
			printf("lol\n");
			++(*tm)->x;
			first_ln = first_ln >> (unsigned int)1;
		}
		else
		{
			printf("lmao\n");
			first_ln = *tm[0]->bitfield; // CHECK THIS
			(*tm)->x = 0;
			++(*tm)->y;
		}
	}
	if ((*tm)->y + (*tm)->height > size)
		return ((*tm)->symbol);
*/
//Check if rest of tetrimino lines fit
//	int tm_i;
	int res;
	int res2;

	res2 = 0;
	res = 0;
	int i = 0;
//	tm_i = 0;
/*	i = (*tm)->y + 1;
	while (i < size && (*tm)->bitfield[tm_i] > 0 && !fit_line(bb[i++], (*tm)->bitfield[tm_i], (*tm)->x))
		tm_i++;
	if (tm_i == (*tm)->height)
	{	
*/		if (!find_place(bb, *tm, size))
		{
			return ((*tm)->symbol);
		}
		while(i < (*tm)->height)
		{
			bb[(*tm)->y + i] |= ((*tm)->bitfield[i] >> (*tm)->x);
			++i;
		}
		//If this block fits, call function for next block
		res = solve_it(bb, tm + 1, size);
//		print_bit(bb, size);
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
//	}
	//Check if block could be moved and if so then call function for same block
/*	if (can_it_move(**tm, size) || (*tm)->y + (*tm)->height <= size)
	{
		//If this block doesn't fit, call function for this block again.
		res = solve_it(bit_board, tm, size);
		if (res == 1)
			return (res);
	}
*/
	if (res2 == 1)
		return (res2);
	(*tm)->x = 0;
	(*tm)->y = 0;
	return (res);
//	return ((*tm)->symbol);
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

void	cpy_tetriminios(t_tetri *tm_cpy, t_tetri **tm, int direction)
{
	int i;

	i = 0;
	if (direction == -1)
	{
		while(tm[i] != NULL)
		{
			tm_cpy[i] = *(tm[i]);
			++i;
		}
	}
	if (direction == 1)
	{
		while(tm[i] != NULL)
		{
			*(tm[i]) = tm_cpy[i];
			++i;
		}
	}
}

void debug(t_tetri **tm)
{
	int i;

	i = 0;
	while (tm[i] != NULL)
	{
//		printf("%c.\t%d\t%d\n", tm[i]->symbol, tm[i]->x, tm[i]->y);	
//		printf("%c ", tm[i]->symbol);	
		++i;
	}
//	printf("\n");
	return ;
}

int opt_calc(int n)
{
	int result;

	result = 0;
	while (n)
		result += n--;
	return(result);
}

void tetri_swap(t_tetri **a, t_tetri **b)
{
	t_tetri	temp;

	temp = **a;
	**a = **b;
	**b = temp;
}

void swap_tetri(t_tetri **tm, int length)
{
	int small;
	int big;
	int i;

	i = 0;
	big = 0;
	small = 0;
	//search the rightmost symbol which is smaller than symbol on its right
	while (tm[i + 1] != NULL && i + 1 < length)
	{
//		printf("i: %d, length: %d\n", i, length);
		if (tm[i]->symbol < tm[i + 1]->symbol)
			small = i;
		++i;
	}
	//find the smallest bigger symbol from its right side
	big = small + 1;
	i = small;
	while (tm[i] != NULL && i < length)
	{
		if (tm[i]->symbol > tm[small]->symbol && tm[i]->symbol < tm[big]->symbol)
			big = i;
		++i;
	}
	//swap
	tetri_swap(&tm[small], &tm[big]);
//	debug(tm);
	i -= 1;
	int middle = small + ((i - small) / 2);
//	printf("small: %d, i: %d, middle: %d\n", small, i, middle);
	while (i > middle)
	{
		++small;
		tetri_swap(&tm[small], &tm[i]);
		--i;
	}
//	debug(tm);
	return;
}

char *create_inverted_alpha(char *a)
{
	int i;
	int ch;

	i = 0;
	ch = 'Z';
	while (i < 26)
	{
		a[i] = ch;
		++i;
		--ch;
	}
	return (a);
}

int compare_alpha(t_tetri **tm, int traverse_n)
{
	int i;
	char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	i = 0;
//	--traverse_n;
//	printf("start\n");
	while(traverse_n - i)
	{
//		printf("i: %d, Traverse: %d, Tm symbol: %c, inverted symbol: %c\n", i, traverse_n, tm[i]->symbol, alpha[traverse_n - i - 1]);
		if (tm[i]->symbol != alpha[traverse_n - i - 1])
			return (0);
		++i;
	}
//	printf("end\n");
	return (1);
}

int count_traverse(int ch, t_tetri **tm)
{
	int i;

	i = 0;
	while(tm[i]->symbol != ch)
		++i;
	return (i + 1);
}

int main(int argc, char **argv)
{
	char			buff[26 * 21 + 1] = {'\0'};
	unsigned int	bit_board[16] = {0};
	t_tetri			*tetriminos[26 + 1] = {NULL};
	t_tetri			tm_cpy[26 + 1] = {NULL};
	int bytes;
	int fd;
	int i;
	int size;
	int count;

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
//			printf("Res: %d\n", res);
			return (-1);
			}
	}
	char_to_bit(buff, bytes, tetriminos);
	count = 0;
	cpy_tetriminios(tm_cpy, tetriminos, -1);
	int block_n;
	int res;
	int traverse_n;

	res = 0;
	traverse_n = 0;
	block_n = bytes / 21 + 1;
	size = 2;
	while (size * size < block_n * 4)
		++size;
	while(res != 1)
	{
		res = solve_it(bit_board, tetriminos, size);  
//		printf("Res: %c\n", res);
		if (res != 1 && count_traverse(res, tetriminos) > traverse_n)
		{
//			cpy_tetriminios(tm_cpy, tetriminos, -1);
			traverse_n = count_traverse(res, tetriminos);
		}
		else if(res == 1)
			break ;
		debug(tetriminos);
//		printf("travers: %d, size: %d\n", traverse_n, size);
		++count;
//		if (count == 20)
//			break ;
//		printf("first: %c, second: %c\n", (*tetriminos)->symbol, (*(tetriminos + (block_n - 1)))->symbol);
//		if (compare_alpha(tetriminos, traverse_n))
//		{
//			cpy_tetriminios(tm_cpy, tetriminos, 1);
			++size;
			count = 0;
//			traverse_n = 0; //TODO this?
//		}
//		else
//		{
//			swap_tetri(tetriminos, traverse_n);		
//		}
//		print_bit(bit_board, size);
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
//	printf("before print size: %d\n", size);
//	debug(tetriminos);
//	printf("\n");
	printer(size, tetriminos);
	free_tetri(tetriminos);	
	return(0);
}
