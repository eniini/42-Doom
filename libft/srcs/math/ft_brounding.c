/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brounding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:00:03 by esormune          #+#    #+#             */
/*   Updated: 2021/04/29 02:30:30 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	ft_compare(long double nb, long double save,
	long double compare, int prec)
{
	long double	x;

	x = ft_neg_pow_ten(1, prec);
	if (nb > 5.0)
		save = save + x;
	else if (nb == 5.0 && prec > 0)
	{
		compare = compare * (ft_pow(10, prec - 1));
		compare = (compare - (intmax_t)compare);
		compare = (compare * 10);
		if ((intmax_t)compare % 2 != 0)
			save = save + x;
	}
	else if (nb == 5.0 && prec <= 0)
	{
		if ((intmax_t)compare % 2 != 0)
			save = save + 0.5;
	}
	return (save);
}

long double	ft_brounding(long double nb, int prec)
{
	long double	save;
	long double	compare;
	int			i;

	if (prec < 0)
		prec = 0;
	save = nb;
	compare = nb;
	i = 0;
	nb = nb - (intmax_t)nb;
	while (i < prec)
	{
		nb = nb * 10;
		nb = nb - (int)nb;
		i++;
	}
	nb = nb * 10;
	return (ft_compare(nb, save, compare, prec));
}
