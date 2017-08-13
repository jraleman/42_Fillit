/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 09:53:46 by jaleman           #+#    #+#             */
/*   Updated: 2016/11/16 09:53:48 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

/*
** Display a usage message on how to use fillit. :)
** Function ft_progname(), will output in a string, the name of the program.
*/

static void		fillit_usage(char *argv0)
{
	ft_putstr("usage: ");
	ft_putstr(argv0);
	ft_putstr(" [fillit_file]\n");
}

/*
** Prints the map after the smallest square made up with the given tetrominos
** is finally found. This will be the output of the program.
*/

static void		fillit_print_map(char **map)
{
	size_t		i;
	size_t		len;

	i = -1;
	len = ft_strlen(*map);
	while (++i < len)
	{
		ft_putstr(map[i]);
		ft_putchar('\n');
	}
}

/*
** If the number of arguments isn't equal to two (2), it will print the usage
** message.
**
** If there is an error while opening the file, the output will print "error",
** then it closes the file.
**
** If the reading is successfull (there is at least one tetromino in the map),
** and if the file is not empty, we will solve the map, by assigning the correct
** to the tetrominos, solving the map with the given tetrominos, and then
** printing the smallest possible square formed with the tetrominos.
*/

int				main(int argc, char *argv[])
{
	int			fd;
	char		**map;
	t_tetromino *tetrominos;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			ft_putstr("error\n");
		else if ((map = fillit_read(fd)) && (ft_strlen(map[0])) && \
				(!map[g_num_tets - 1][TETROMINO_SIZE - 1]))
		{
			tetrominos = fillit_tetromino(map);
			map = fillit_solve(tetrominos);
			fillit_print_map(map);
			free(tetrominos);
			ft_memdel((void **)map);
		}
		else
			ft_putstr("error\n");
		close(fd);
	}
	else
		fillit_usage(argv[0]);
	return (0);
}
