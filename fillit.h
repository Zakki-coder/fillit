/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:28:13 by jniemine          #+#    #+#             */
/*   Updated: 2022/02/10 12:43:25 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_tetrimino
{
	unsigned int	*bitfield;
	int				x;
	int				y;
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
	int				height;
	int				width;
	char			symbol;
}					t_tetri;

#endif
