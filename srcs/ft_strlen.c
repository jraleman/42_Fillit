/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <thendric@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 10:31:41 by thendric          #+#    #+#             */
/*   Updated: 2016/11/02 10:36:24 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

size_t		ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	while (*str)
		str++;
	return ((size_t)(str - s));
}
