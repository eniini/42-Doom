/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rotation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:56:50 by eniini            #+#    #+#             */
/*   Updated: 2021/09/03 18:04:55 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
*	  A
*	  |\		X is always (x, 0).
*	  |α\		solving [α(CAB) = BC / AC] gives us angle α,
*	  |  \		and using formula	[α = atan(OX / AO)]
*	  |   \ 	we can solve		[AO * tan(α) = 0X].
*	  |    \
*	<-O-----X--->
*	  |      \
*	  |       \
*	  |        \
*	  C---------B
*	  |
*	  v
*/

/*
*	[p] is a point with a positive y value, [n] is a negative value we want
*	to project into the x-axis.
*	if [p.x] is a negative value, we know that the calculated triangle is
*	left-facing which changes how the formula translates to world space.
*/
static t_vert	project_point_to_axis(t_vert p, t_vert n)
{
	t_vert	result;
	int		side;
	double	a_tan;

	result.y = 0;
	side = abs(p.y) + abs(n.y);
	if (p.x <= 0)
	{
		a_tan = RAD_TO_DEG * atan((abs(n.x - p.x) / (double)side));
		result.x = (short)round(tan(a_tan * DEG_TO_RAD) * p.y);
		if (p.x > n.x)
			result.x = p.x - result.x;
		else
			result.x = p.x + result.x;
	}
	else
	{
		a_tan = RAD_TO_DEG * atan((abs(p.x - n.x) / (double)side));
		result.x = (short)round(tan(a_tan * DEG_TO_RAD) * p.y);
		result.x = p.x - result.x;
	}
	return (result);
}

/*
*	Intermediary function to sort and update given LINEDEF according to if
*	its crossing into or from the negative Y space.
*/
static void	update_visvert(t_world *world, t_vert start, t_vert end, int mode)
{
	if (mode == 1)
	{
		world->v_walls[world->v_wallcount].start = start;
		world->v_walls[world->v_wallcount].end = end;
	}
	else if (mode == 2)
	{
		world->v_walls[world->v_wallcount].start = \
		project_point_to_axis(start, end);
		world->v_walls[world->v_wallcount].end = end;
	}
	else if (mode == 3)
	{
		world->v_walls[world->v_wallcount].start = start;
		world->v_walls[world->v_wallcount].end = \
		project_point_to_axis(start, end);
	}
	world->v_wallcount++;
}

/*
*	Because player's orientation is perpendicular to Y-axis,
*	any negative vertices are ignored for rendering purposes.
*	For that reason, all LINEDEFS that cross into/to negative coordinates are
*	cut at the Y-axis.
*/
void	cull_vertices(t_world *world)
{
	int	i;

	i = 0;
	world->v_wallcount = 0;
	while (i < world->vertcount - 1)
	{
		world->v_walls[world->v_wallcount].color = wall_colortable(i);
		if (world->p_verts[i].y >= 0 && world->p_verts[i + 1].y >= 0)
			update_visvert(world, world->p_verts[i], world->p_verts[i + 1], 1);
		else if (world->p_verts[i].y < 0 && world->p_verts[i + 1].y > 0)
			update_visvert(world, world->p_verts[i], world->p_verts[i + 1], 2);
		else if (world->p_verts[i].y > 0 && world->p_verts[i + 1].y < 0)
			update_visvert(world, world->p_verts[i], world->p_verts[i + 1], 3);
		i++;
	}
	world->v_walls[world->v_wallcount].color = wall_colortable(i);
	if (world->p_verts[i].y >= 0 && world->p_verts[0].y >= 0)
		update_visvert(world, world->p_verts[i], world->p_verts[0], 1);
	else if (world->p_verts[i].y < 0 && world->p_verts[0].y > 0)
		update_visvert(world, world->p_verts[i], world->p_verts[0], 2);
	else if (world->p_verts[i].y > 0 && world->p_verts[0].y < 0)
		update_visvert(world, world->p_verts[i], world->p_verts[0], 3);
}

/*
*	Applies a 2d matrix rotation around the origin / player to every
*	vertex inside given map. (currently all vertices). So in fact this rotates
*	the entire world around the player.
*	! Because our Y-axis points down, this rotates clockwise. Player's viewangle
*	rotates the opposite.
*/
void	rotate_player(t_world *w, t_mmap *mmap, int r)
{
	int		i;
	double	c;
	double	s;

	i = 0;
	w->w_angle += r;
	w->w_angle = w->w_angle % 360;
	c = cos(w->w_angle * DEG_TO_RAD);
	s = sin(w->w_angle * DEG_TO_RAD);
	while (i < w->vertcount)
	{
		w->p_verts[i].x = (short)round(w->verts[i].x * c - w->verts[i].y * s);
		w->p_verts[i].y = (short)round(w->verts[i].x * s + w->verts[i].y * c);
		i++;
	}
	mmap->mm_p_angle.x = (short)round((w->p_angle.x * c) + (w->p_angle.y * s));
	mmap->mm_p_angle.y = (short)round((w->p_angle.x * -s) + (w->p_angle.y * c));
}
