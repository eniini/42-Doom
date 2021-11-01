/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_neg_minus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 02:14:36 by esormune          #+#    #+#             */
/*   Updated: 2021/04/29 02:15:14 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_neg_minus(double nb)
{
	unsigned long long	*x;
	int					ret;

	x = (unsigned long long *)&nb;
	ret = (*x >> 63);
	if (ret == 1)
		return (-1);
	return (1);
}
