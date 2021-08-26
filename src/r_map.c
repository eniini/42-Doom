#include "doom.h"

void	draw_map(t_map *map, t_world *world)
{
	int		i;

	i = 0;
	while (i < world->vertcount - 1)
	{
		draw_line(map->mapbuf, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * \
			world->verts[i].x, map->mapbuf->h / 2 + map->buf_unit.y * \
			world->verts[i].y}, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * \
			world->verts[i + 1].x, map->mapbuf->h / 2 + map->buf_unit.y * \
			world->verts[i + 1].y}, MAP_C_WALL);
		i++;
	}
	draw_line(map->mapbuf, (t_point){map->mapbuf->w / 2 + map->buf_unit.x * world->verts[0].x, \
		map->mapbuf->h / 2 + map->buf_unit.y * world->verts[0].y}, \
		(t_point){map->mapbuf->w / 2 + map->buf_unit.x * world->verts[i].x, \
		map->mapbuf->h / 2 + map->buf_unit.y * world->verts[i].y}, MAP_C_WALL);
	i = 0;
	while (i < world->vertcount)
	{
		draw_pixel(map->mapbuf->w / 2 + map->buf_unit.x * world->verts[i].x, \
		map->mapbuf->h / 2 + map->buf_unit.y * world->verts[i].y, map->mapbuf, \
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
