/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:42:14 by jaleman           #+#    #+#             */
/*   Updated: 2016/11/13 02:42:14 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

/*
** Library fcntl.h included to be able to use open(), read().
*/

# include <fcntl.h>

/*
** Library stdlib.h included to be able to use free()
*/

# include <stdlib.h>

/*
** Library unistd.h included to be able to use close()
*/

# include <unistd.h>

/*
** Macros for empty, blocks, and letter characters.
*/

# define EMPTY '.'
# define BLOCK '#'
# define LETTER 'A'
# define NEW_LINE '\n'

/*
** Macros for tetromino width, size, and the max numbers of tetromino.
*/

# define SIZE 4
# define TETROMINO_SIZE 21
# define TETROMINO_MAX_TOTAL (26 - (LETTER - 'A'))

/*
** Macro for buffer size (the biggest file can only be 546 bytes + 1).
*/

# define BUFFER_SIZE TETROMINO_SIZE * TETROMINO_MAX_TOTAL

/*
** Global variable for number of tetriminos
*/

int		g_num_tets;

/*
** Structures of a tetromino, defining the coordinates by its x and y values,
** the number of the tetromino (if it's the first one, second one, etc...).
*/

typedef struct			s_tetromino
{
	char				letter;
	int					x[4];
	int					y[4];
	int					width;
	int					height;
	struct s_tetromino	*next;
}						t_tetromino;

/*
** Prototypes for libft functions
*/

void					ft_bzero(void *s, size_t n);
char					**ft_strsplit(char const *s, char c);
void					ft_putchar(char c);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putstr(char const *s);
size_t					ft_strlen(const char *s);
void					ft_memdel(void **ap);
void					*ft_memset(void *b, int c, size_t len);
double					ft_sqrt(double x);
size_t					ft_wordcount(const char *s, char c);
size_t					ft_wordlen(const char *s, char c);

/*
** Prototypes for fillit type functions.
*/

char					**fillit_read(int fd);
char					**fillit_create_map(int size);
char					**fillit_solve(t_tetromino *tet);
t_tetromino				*fillit_tetromino(char **map);

#endif
