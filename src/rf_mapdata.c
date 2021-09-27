/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rf_mapdata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:41:37 by eniini            #+#    #+#             */
/*   Updated: 2021/09/27 22:10:19 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	add_editordata(t_rf *rf, t_debug_room *debugdata)
{
	return ;
}

t_bool	add_mapdata_to_rf(t_rf *rf, t_debug_room *debugdata)
{
	if (!rf)
		ft_getout("no active filedescriptor!");
	if (!debugdata)
		ft_getout("no mapdata struct found!");
	add_editordata_to_rf(rf, debugdata);
}

void	load_mapdata_from_rf(t_rf *rf, t_mapdata *mapdata)
{
	int	i;

	i = 0;
	while (i <= RF_MAPTYPES)
	{
		if (!(load_maplump_from_rf(rf, mapdata, i)))
			ft_getout("failed to load essential mapdata from RF!");
		i++;
	}
}
