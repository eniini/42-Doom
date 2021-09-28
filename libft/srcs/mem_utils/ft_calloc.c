/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:32:06 by esormune          #+#    #+#             */
/*   Updated: 2021/09/28 22:08:17 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	Allocates memory for a pointer to [count] * [size] and zeroes it.
*	Returns a (void *) to allocated memory or NULL on failure.
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!count || !size)
		return (NULL);
	ptr = (void *)malloc(size * count);
	if (!(ptr))
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
