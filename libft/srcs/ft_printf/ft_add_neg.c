/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_neg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:20:03 by esormune          #+#    #+#             */
/*   Updated: 2021/05/17 14:21:37 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Returns a 1 or a 0 based on if the character is a '-'. This is then
** used to calculate the appropriate size for the string.
*/

int	ft_add_neg(char c)
{
	if (c == '-')
		return (1);
	else
		return (0);
}
