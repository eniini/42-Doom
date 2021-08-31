#include "doom.h"

/*
*	TODO: probably not ideal to malloc a new list of verts every time player
*	rotates view, think of alternatives!
*/
void	cull_vertices(t_world *world)
{
	int		i;

	i = 1;
	if (world->v_verts)
		free(world->v_verts);
	world->v_vertcount = 0;
	world->v_verts = (t_vert *)malloc(sizeof(t_vert) * world->vertcount);
	if (!world->v_verts)
		ft_getout("failed to malloc visible vertex array!");
	while (i < world->vertcount - 1)
	{
		if (world->p_verts[i].y > 0 || world->p_verts[i + 1].y > 0)
		{
			if (world->p_verts[i].y > 0)
				world->v_verts[world->v_vertcount] = world->p_verts[i];
			else
				world->v_verts[world->v_vertcount] = (t_vert){world->p_verts[i].x, 0};
			/*if (world->v_verts[world->v_vertcount].y)
			{
				world->v_verts[world->v_vertcount].x /= \
				world->v_verts[world->v_vertcount].y; //emulate distance projection
			}*/
			world->v_vertcount++;
		}
		i++;
	}
}

void	draw_visibleverts(t_map *map, t_world *world)
{
	int		i;

	i = 0;
	while (i < world->v_vertcount - 1)
	{
		draw_line(map->mapbuf, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * \
			world->v_verts[i].x, map->mapbuf->h / 2 + map->buf_unit.y * \
			world->v_verts[i].y}, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * \
			world->v_verts[i + 1].x, map->mapbuf->h / 2 + map->buf_unit.y * \
			world->v_verts[i + 1].y}, MAP_C_WALL);
		i++;
	}
	i = 0;
	while (i < world->v_vertcount)
	{
		draw_pixel(map->mapbuf->w / 2 + map->buf_unit.x * world->v_verts[i].x, \
		map->mapbuf->h / 2 + map->buf_unit.y * world->v_verts[i].y, map->mapbuf, \
		MAP_C_VERTICE);
		i++;
	}
}

void	draw_map(t_map *map, t_world *world)
{
	int		i;

	i = 0;
	while (i < world->vertcount - 1)
	{
		draw_line(map->mapbuf, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * \
			world->p_verts[i].x, map->mapbuf->h / 2 + map->buf_unit.y * \
			world->p_verts[i].y}, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * \
			world->p_verts[i + 1].x, map->mapbuf->h / 2 + map->buf_unit.y * \
			world->p_verts[i + 1].y}, MAP_C_WALL);
		i++;
	}
	draw_line(map->mapbuf, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * \
		world->p_verts[0].x, map->mapbuf->h / 2 + map->buf_unit.y * \
		world->p_verts[0].y}, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * \
		world->p_verts[i].x, map->mapbuf->h / 2 + map->buf_unit.y * \
		world->p_verts[i].y}, MAP_C_WALL);
	i = 0;
	while (i < world->vertcount)
	{
		draw_pixel(map->mapbuf->w / 2 + map->buf_unit.x * world->p_verts[i].x, \
		map->mapbuf->h / 2 + map->buf_unit.y * world->p_verts[i].y, map->mapbuf, \
		MAP_C_VERTICE);
		i++;
	}
	draw_line(map->mapbuf, (t_point){map->mapbuf->w / 2, map->mapbuf->h / 2}, \
		(t_point){(map->mapbuf->w / 2) + (map->buf_unit.x * world->p_angle.x), \
		(map->mapbuf->h / 2) + (map->buf_unit.y * world->p_angle.y)}, \
		MAP_C_PLAYERLOOK);
	draw_circle(map->mapbuf, (t_point){map->mapbuf->w / 2, map->mapbuf->h / 2}, \
	10, MMAP_C_PLAYER);
}

/*
*	Applies a 2d matrix rotation around the origin / player to every
*	vertex inside given map. (currently all vertices). So in fact this rotates
*	the entire world around the player.
*	! Because our Y-axis points down, this rotates clockwise.
*/
void	rotate_player(t_world *w, t_mmap *mmap, int r)
{
	int		i;
	double	c;
	double	s;

	i = 0;
	w->w_angle += r;
	w->w_angle = w->w_angle % 360;
	c = cos(w->w_angle * RAD_CON);
	s = sin(w->w_angle * RAD_CON);
	while (i < w->vertcount)
	{
		w->p_verts[i].x = (short)round(w->verts[i].x * c - w->verts[i].y * s);
		w->p_verts[i].y = (short)round(w->verts[i].x * s + w->verts[i].y * c);
		i++;
	}
	i = 0;
	while (i < w->v_vertcount)
	{
		w->v_verts[i].x = (short)round(w->verts[i].x * c - w->verts[i].y * s);
		w->v_verts[i].y = (short)round(w->verts[i].x * s + w->verts[i].y * c);
		i++;
	}
	mmap->mm_p_angle.x = (short)round((w->p_angle.x * c) - (w->p_angle.y * s));
	mmap->mm_p_angle.y = (short)round((w->p_angle.x * s) + (w->p_angle.y * c));
}
