/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brounding_ld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:19:48 by esormune          #+#    #+#             */
/*   Updated: 2021/04/29 02:30:23 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_exact(long double nb, int prec)
{
	char	buf[100];
	size_t	units;
	size_t	whole_nb;
	int		i;

	i = 0;
	ft_bzero(buf, 100);
	units = (size_t)nb;
	nb = nb - units;
	while (i <= prec)
	{
		nb = nb * 10;
		buf[i] = (char)((int)nb + 48);
		nb = nb - (int)nb;
		i++;
	}
	whole_nb = ft_atoi_max(buf);
	if (whole_nb % ft_uintmax_pow(5, prec + 1) == 0)
		return (1);
	else
		return (0);
}

static long double	ft_compare(long double nb, long double save,
	long double compare, int prec)
{
	long double	x;

	x = ft_neg_pow_ten(5, prec + 1);
	if (nb < 5.0)
		return (save);
	else if (nb == 5.0 && prec > 0 && ft_is_exact(save, prec))
	{
		compare = compare * (ft_pow(10, prec - 1));
		compare = (compare - (intmax_t)compare);
		compare = (compare * 10);
		if ((intmax_t)compare % 2 != 0)
			save = save + x;
	}
	else if (nb == 5.0 && prec <= 0 && ft_is_exact(save, prec))
	{
		if ((intmax_t)compare % 2 != 0)
			save = save + 0.5;
	}
	else
		save = save + x;
	return (save);
}

long double	ft_brounding_ld(long double nb, int prec)
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
