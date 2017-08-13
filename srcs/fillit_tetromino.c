/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_tetromino.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <thendric@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 04:40:48 by thendric          #+#    #+#             */
/*   Updated: 2016/11/21 04:40:48 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

/*
** Set the correct dimensions, width and height, to the tetromino.
** If the row x coordinate is equal to the col x coordinate, we increment the
** width. Same way with the height, just swaping x with y. If the division of
** width or height by SIZE (4) isn't exact, we increment to both width and
** height by four (4), to have the correct values of those weirds tetrominos.
** The -1 in both row and col is because... you guessed it, the fucking norm.
*/

static void				fillit_set_dimensions(t_tetromino *tet)
{
	int		row;
	int		col;
	int		width;
	int		height;

	row = -1;
	width = 0;
	height = 0;
	while (++row < SIZE)
	{
		col = -1;
		while (++col < SIZE)
		{
			(tet->x[row] == tet->x[col]) ? width += 1 : width;
			(tet->y[row] == tet->y[col]) ? height += 1 : height;
		}
	}
	if ((width % SIZE) || (height % SIZE))
	{
		width += 4;
		height += 4;
	}
	tet->width = (width / 4);
	tet->height = (height / 4);
}

/*
** Split the map (2D Array) to convert it to fullmap (3D Array), so we can
** work with the number of the tetrominos (working as an ID for each one).
*/

static char				***fillit_split_tetromino(char **map)
{
	int		i;
	char	***fullmap;

	i = 0;
	if (!(fullmap = (char ***)malloc(sizeof(char **) * g_num_tets + 1)))
		return (NULL);
	while (i < g_num_tets)
	{
		fullmap[i] = ft_strsplit(map[i], '\n');
		i += 1;
	}
	return (fullmap);
}

/*
** Makes new tetrominos by mallocing them. We will give the size of the
** t_tetromino type, to allocate them correctly.
*/

static t_tetromino		*fillit_new_tetrominos(int size)
{
	int			i;
	t_tetromino	*new;
	t_tetromino *head;

	if (!(new = (t_tetromino *)malloc(sizeof(t_tetromino) + 1)))
		return (NULL);
	head = new;
	i = 0;
	while (i++ < size)
	{
		if (!(new->next = (t_tetromino *)malloc(sizeof(t_tetromino) + 1)))
			return (NULL);
		new = new->next;
	}
	ft_memset(new, 0, (sizeof(t_tetromino) + 1));
	return (head);
}

/*
** Creates new tetrominos by assigning the x and y coordinates of every block
** into its structure, and also assigning the letter (A, B, C...) into its
** structure. We used an array of counters because of the fucking norm.
** The counters represent:
** Counter[0] = Number of tetrominos.
** Counter[1] = Rows of the tetromino.
** Counter[2] = Columns of the tetromino.
** Counter[3] = X and Y coordinates of the position of the tetromino.
**
** Every tetromino gets assigned a certain letter. Starting from the first one,
** then the second one gets assigned the next letter, and so on and so forth.
** Example: tetromino1 -> A; tetromino2 -> B; tetromino3 -> C; ...
*/

static t_tetromino		*fillit_create_tetrominos(char ***fullmap, \
						t_tetromino *tet, char letter, int *counter)
{
	t_tetromino *head;

	head = tet;
	counter[0] = -1;
	while (++counter[0] < g_num_tets)
	{
		counter[3] = 0;
		counter[1] = -1;
		while (++counter[1] < SIZE)
		{
			counter[2] = -1;
			while (++counter[2] < SIZE)
			{
				if (fullmap[counter[0]][counter[1]][counter[2]] == BLOCK)
				{
					tet->x[counter[3]] = counter[1];
					tet->y[counter[3]++] = counter[2];
				}
			}
		}
		fillit_set_dimensions(tet);
		tet->letter = letter++;
		tet = tet->next;
	}
	return (head);
}

/*
** Pretty much call all the other functions, and returns the newly created
** tetrominos from the map. In this function, the array of counter is defined.
*/

t_tetromino				*fillit_tetromino(char **map)
{
	int				*counter;
	char			***fullmap;
	t_tetromino		*tetromino;

	if (!(counter = (int *)malloc(sizeof(int) * 4)))
		return (NULL);
	if (!(fullmap = (char ***)malloc(sizeof(char **) * g_num_tets + 1)))
		return (NULL);
	tetromino = fillit_new_tetrominos(g_num_tets);
	fullmap = fillit_split_tetromino(map);
	return (fillit_create_tetrominos(fullmap, tetromino, LETTER, counter));
}
