/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 22:33:11 by jaleman           #+#    #+#             */
/*   Updated: 2016/11/24 22:33:11 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

/*
** Function to set the tetrominos on the map. We replace the coordinates on the
** map, by the letter of the current tetromino.
*/

static void	fillit_set_tetromino(t_tetromino *tet, char **map, int y, int x)
{
	int		row;
	int		col;
	int		i;

	i = 0;
	col = 0;
	while (tet->height > col)
	{
		row = 0;
		while (tet->width > row)
		{
			if (tet->x[i] == col && tet->y[i] == row)
			{
				map[col + y][row + x] = tet->letter;
				i += 1;
			}
			row += 1;
		}
		col += 1;
	}
}

/*
** This checks if there can be a tetromino placed in the map. It goes into a
** while loop, looking for that empty space. If it doesn't find one, it means
** that a tetromino can't be placed here. If it finds one, it will place the
** tetromino :)
*/

static int	fillit_check_placement(t_tetromino *tet, char **map, int y, int x)
{
	int		row;
	int		col;
	int		i;

	i = 0;
	col = 0;
	while (tet->height > col)
	{
		row = 0;
		while (tet->width > row)
		{
			if (tet->x[i] == col && tet->y[i] == row && i < SIZE)
			{
				if (map[col + y][row + x] != EMPTY)
					return (0);
				i += 1;
			}
			row += 1;
		}
		col += 1;
	}
	fillit_set_tetromino(tet, map, y, x);
	return (1);
}

/*
** Moves the tetrominos to the top-left corner, so we can start from there.
** This DOESN'T PLACE them, but just put the coordinates in there. I don't
** think I have to mention why the -1 in the counter... ;)
*/

static void	fillit_move_tetromino_upperleft(t_tetromino *tet)
{
	int			i;
	int			pos_x;
	int			pos_y;

	while (tet)
	{
		i = -1;
		pos_x = SIZE - 1;
		pos_y = SIZE - 1;
		while (++i < SIZE)
		{
			if (tet->x[i] < pos_x)
				pos_x = tet->x[i];
			if (tet->y[i] < pos_y)
				pos_y = tet->y[i];
		}
		i = -1;
		while (++i < SIZE)
		{
			tet->x[i] -= pos_x;
			tet->y[i] -= pos_y;
		}
		tet = tet->next;
	}
}

/*
** This is where the real shit happens. This function will call itself (being
** recursive), and will see if a solution can be found inside the map. If it
** fails to, it's going to return a zero (0), indicating that a solution
** couldn't be found with the current map. If a tetromino can be placed, it'll
** do the recursion. If it fails, we will set the tetromino empty, and then
** asign it's old value (the letter) back. If this function finds a solution,
** it's going to return a one (1).
*/

static int	fillit_solve_map(char **map, t_tetromino *tet, int size)
{
	int		x;
	int		y;
	char	letter;

	if (!tet->next)
		return (1);
	y = -1;
	letter = tet->letter;
	while (++y <= (size - tet->height))
	{
		x = -1;
		while (++x <= (size - tet->width))
		{
			if (fillit_check_placement(tet, map, y, x))
			{
				if (fillit_solve_map(map, tet->next, size))
					return (1);
				tet->letter = EMPTY;
				fillit_set_tetromino(tet, map, y, x);
				tet->letter = letter;
			}
		}
	}
	return (0);
}

/*
** The size of map will be the square root of the number of tetrominos in the
** file, time the size of the blocks (SIZE == 4), and then we move coordinates
** of the tetromino to the top-left corner. Then we enter into the real shit,
** the recursive function. If a solution isn't found, we will delete the map,
** increment the size, and create a new map with this size. This will be going
** until a solution is found. :D
*/

char		**fillit_solve(t_tetromino *tet)
{
	char	**map;
	int		size;

	if (!tet)
		return (NULL);
	size = ft_sqrt(g_num_tets * SIZE);
	map = fillit_create_map(size);
	fillit_move_tetromino_upperleft(tet);
	while (!fillit_solve_map(map, tet, size))
	{
		ft_memdel((void **)map);
		size += 1;
		map = fillit_create_map(size);
	}
	return (map);
}
