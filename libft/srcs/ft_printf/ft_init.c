/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:40:55 by esormune          #+#    #+#             */
/*   Updated: 2021/05/17 15:01:38 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Initialises and mallocs space for the printf struct, including
** the array of strings and the length array.
*/

t_printf	*ft_init(char *str)
{
	t_printf	*res;
	int			i;

	res = (t_printf *)malloc(sizeof(t_printf));
	if (!res)
		return (NULL);
	res->strings = ft_split(str);
	if (!(res->strings))
		return (NULL);
	i = 0;
	while (res->strings[i] != NULL)
		i++;
	res->lengths = (size_t *)malloc(sizeof(size_t) * (i));
	if (!(res->lengths))
		return (NULL);
	return (res);
}

/*
** Frees all allocated memory from the t_printf struct. In other words, the
** reverse of init.
*/

void	ft_rev_init(t_printf *res)
{
	ft_free_array(res->strings);
	free(res->lengths);
	free(res);
}
