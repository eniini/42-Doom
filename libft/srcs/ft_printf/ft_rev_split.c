/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:22:18 by esormune          #+#    #+#             */
/*   Updated: 2021/05/17 15:09:39 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Takes the array and makes it into a string. Returns size of string.
*/

static int	ft_form_string(t_printf *res, char *str)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	while (res->strings[i] != NULL)
	{
		x = 0;
		while ((size_t)x < res->lengths[i])
			str[y++] = res->strings[i][x++];
		i++;
	}
	str[y] = '\0';
	ft_putnstr(str, y);
	return (y);
}

/*
** Implodes the array back into a string with consideration to NULL chars
** and therefore uses defined lengths instead of "until '\0'". Prints the
** string. Returns value for printf.
*/

int	ft_rev_split(t_printf *res)
{
	char	*str;
	size_t	size;
	int		i;
	int		y;

	i = 0;
	size = 0;
	while (res->strings[i] != NULL)
		size = size + res->lengths[i++];
	str = ft_calloc((size + 1), sizeof(char));
	if (!str)
		return (-1);
	y = ft_form_string(res, str);
	free(str);
	return (y);
}
