/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:19:07 by esormune          #+#    #+#             */
/*   Updated: 2021/05/17 13:38:00 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Takes the array and makes it into a string. Returns size of string.
*/

static int	ft_form_string(t_printf *res, char *str, int fd)
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
	ft_putnstr_fd(str, y, fd);
	return (y);
}

/*
** Prints the string onto the file descriptor. Returns size for dprintf
** return.
*/

static int	ft_drev_split(t_printf *res, int fd)
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
	y = ft_form_string(res, str, fd);
	free(str);
	return (y);
}

/*
** A variation of printf that prints the output onto the file descriptor
** instead of STDOUT.
*/

int	ft_dprintf(int fd, const char *format, ...)
{
	t_flags		*data;
	t_printf	*res;
	va_list		list;
	int			ret;

	data = (t_flags *)malloc(sizeof(t_flags));
	if (!data)
		return (-1);
	ft_reset(data);
	res = ft_init((char *)format);
	if (!res)
		return (-1);
	va_start(list, format);
	res->strings = ft_next(res, data, list);
	ret = ft_drev_split(res, fd);
	ft_rev_init(res);
	va_end(list);
	free(data);
	return (ret);
}
