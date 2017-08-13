/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 09:53:46 by jaleman           #+#    #+#             */
/*   Updated: 2016/11/16 09:53:48 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

/*
** Validates the number and values of the characters found in the map (file).
** If something fails, such as having a larger or smaller tetromino width than
** whatever is defined, or having invalid tetromino sizes, it returns zero.
** Counter inside (tetromino[i++] == '\n') because of fucking norm. :)
*/

static int	fillit_valid_characters(char *tetromino)
{
	int		i;
	int		height;
	int		blocks;
	int		characters;

	i = 0;
	blocks = 0;
	characters = 0;
	height = 0;
	while ((tetromino[i] == EMPTY || tetromino[i] == BLOCK || \
		tetromino[i] == '\n') && tetromino[i] && (height != SIZE))
	{
		if (tetromino[i] == EMPTY || tetromino[i] == BLOCK)
		{
			if (tetromino[i] == BLOCK)
				blocks += 1;
			characters += 1;
		}
		if (tetromino[i++] == '\n')
			height += 1;
	}
	if (((characters) == SIZE * SIZE) && (height == SIZE) && \
		(blocks == SIZE) && (tetromino[i] == '\n' || tetromino[i] == '\0'))
		return (1);
	return (0);
}

/*
** Splits the tetromino by lines, and check the neighbour for each block
** characters. Almost of the pieces will add a total of 6 to the counter, but
** the block one, which adds a total of 8. If the tetromino isn't equal to
** those, it's not a valid one. The -1 in both row and col, is because of the
** fucking norm. :) I mean, what's the difference between 24 and 26 lines?!
*/

static int	fillit_valid_tetromino(char **tetromino)
{
	int		cnt;
	int		row;
	int		col;

	cnt = 0;
	row = -1;
	while (SIZE > ++row)
	{
		col = -1;
		while (SIZE > ++col)
		{
			if (tetromino[row][col] == BLOCK && row < 3)
				tetromino[row + 1][col] == BLOCK ? cnt++ : cnt;
			if (tetromino[row][col] == BLOCK && row > 0)
				tetromino[row - 1][col] == BLOCK ? cnt++ : cnt;
			if (tetromino[row][col] == BLOCK && col < 3)
				tetromino[row][col + 1] == BLOCK ? cnt++ : cnt;
			if (tetromino[row][col] == BLOCK && col > 0)
				tetromino[row][col - 1] == BLOCK ? cnt++ : cnt;
		}
	}
	if (cnt == 6 || cnt == 8)
		return (1);
	return (0);
}

/*
** Calls both functions to make sure that there are valid characters and
** valid tetromino in the map.
*/

static int	fillit_valid(char *map)
{
	if (fillit_valid_characters(map))
		if (fillit_valid_tetromino((ft_strsplit(map, '\n'))))
			return (1);
	return (0);
}

/*
** Allocates memory to creat a new map. This function is called inside the
** fillit_solve(), in which, after retrying the function fillit_solve_map()
** recursivley, it will see if it needs to grow the map, hence why we use
** this function. I placed it in this file because of the fucking norm. :)
*/

char		**fillit_create_map(int size)
{
	char	**map;
	int		row;
	int		col;

	if (!(map = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	row = 0;
	while (row < size)
	{
		if (!(map[row] = (char *)malloc(sizeof(char) * size + 1)))
			return (NULL);
		row += 1;
	}
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
			map[row][col++] = EMPTY;
		map[row][col] = '\0';
		row += 1;
	}
	return (map);
}

/*
** Reads a tetromino piece, one by one, and checks if its characters and
** size are right. TETROMINO_SIZE is the total size of a tetromino, it's defined
** by counting all the characters, including '\n', and '\0'. If a tetromino
** isn't valid, it'll return a NULL. If it doesn't find any problem with the
** pieces, it will return the characters read.
*/

char		**fillit_read(int fd)
{
	int		i;
	char	**map;

	i = 0;
	if (!(map = (char **)malloc(sizeof(char *) * BUFFER_SIZE)))
		return (NULL);
	while (i < TETROMINO_MAX_TOTAL)
	{
		if (!(map[i] = (char *)malloc(sizeof(char) * TETROMINO_SIZE)))
			return (NULL);
		ft_bzero(map[i], TETROMINO_SIZE);
		if (!(read(fd, map[i], TETROMINO_SIZE)))
			return (map);
		if (!(fillit_valid(map[i])))
			return (NULL);
		i += 1;
		g_num_tets = i;
	}
	return (NULL);
}
