/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_uintmax_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:44:17 by esormune          #+#    #+#             */
/*   Updated: 2021/04/29 02:46:38 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_save(uintmax_t nb, int neg, int base, int i)
{
	char	*str;
	char	*save;
	char	temp[64 + 1];
	int		x;

	x = 0;
	str = "0123456789ABCDEF";
	while (nb > 0)
	{
		temp[i] = str[nb % base];
		nb = nb / base;
		i++;
	}
	if (neg == -1 && base == 10)
		temp[i++] = '-';
	temp[i] = '\0';
	save = (char *)malloc(sizeof(char) * i + 1);
	if (!(save))
		return (NULL);
	i = i - 1;
	while (i >= 0)
		save[x++] = temp[i--];
	save[x] = '\0';
	return (save);
}

char	*ft_itoa_uintmax_base(uintmax_t nb, int base)
{
	char		*save;
	int			neg;

	if (base < 2 || base > 16)
		return (NULL);
	neg = ft_is_neg_minus(nb);
	if (nb < 0)
		nb = nb * (-1);
	if (nb == 0)
	{
		save = (char *)malloc(sizeof(char) * 2);
		if (!(save))
			return (NULL);
		save[0] = '0';
		save[1] = '\0';
		return (save);
	}
	return (ft_save(nb, neg, base, 0));
}
