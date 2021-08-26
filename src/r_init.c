#include "doom.h"

/*
*	Index through the vertices and find the minimum & maximum values included.
*	Returns the distance between min/max X & Y coordinates of a given
*	room/world/space.
*	if [getmax] is TRUE, returns maximum values.
*	Otherwise returns minimum values.
*/
static t_vert	get_mapdimensions(t_world *world, t_bool getmax)
{
	t_vert			*crawler;
	t_vert			max;
	t_vert			min;
	int				i;

	i = 0;
	max = (t_vert){1, 1};
	min = (t_vert){-1, -1};
	crawler = world->verts;
	while (i < world->vertcount)
	{
		if (crawler->x > max.x)
			max.x = crawler->x;
		if (crawler->y > max.y)
			max.y = crawler->y;
		if (crawler->x < min.x)
			min.x = crawler->x;
		if (crawler->y < min.y)
			min.y = crawler->y;
		crawler++;
		i++;
	}
	if (getmax)
		return (max);
	return (min);
}

void	init_world(t_world *world, t_map *map, t_buffer *buf)
{
	world->player = (t_vert){0, 0};
	world->p_angle = (t_vert){1 * MAP_UNIT, 1 * MAP_UNIT};
	world->vertcount = 8;
	world->verts = malloc(sizeof(t_vert) * world->vertcount);
	if (!world->verts)
		ft_getout("failed to malloc world.verts[]!");
	world->verts[0] = (t_vert){2 * MAP_UNIT, -4 * MAP_UNIT},
		world->verts[1] = (t_vert){4 * MAP_UNIT, 1 * MAP_UNIT},
		world->verts[2] = (t_vert){1 * MAP_UNIT, 1 * MAP_UNIT},
		world->verts[3] = (t_vert){0 * MAP_UNIT, 4 * MAP_UNIT},
		world->verts[4] = (t_vert){-1 * MAP_UNIT, 1 * MAP_UNIT},
		world->verts[5] = (t_vert){-4 * MAP_UNIT, 1 * MAP_UNIT},
		world->verts[6] = (t_vert){-2 * MAP_UNIT, -4 * MAP_UNIT},
		world->verts[7] = (t_vert){0 * MAP_UNIT, -1 * MAP_UNIT};
	map->max_coord = get_mapdimensions(world, TRUE);
	map->min_coord = get_mapdimensions(world, FALSE);
	map->coord_diff.x = map->max_coord.x - map->min_coord.x;
	map->coord_diff.y = map->max_coord.y - map->min_coord.y;
	map->buf_unit.x = ((short)buf->h / map->coord_diff.x);
	map->buf_unit.y = ((short)buf->h / map->coord_diff.y);
	map->mapbuf = buf;
}

void	init_minimap(t_world *w, t_mmap *mmap, t_buffer *buf, uint32_t s)
{
	mmap->max_coord = get_mapdimensions(w, TRUE);
	mmap->min_coord = get_mapdimensions(w, FALSE);
	mmap->coord_diff.x = mmap->max_coord.x - mmap->min_coord.x;
	mmap->coord_diff.y = mmap->max_coord.y - mmap->min_coord.y;
	mmap->buf_unit.x = ((short)buf->h / mmap->coord_diff.x);
	mmap->buf_unit.y = ((short)buf->h / mmap->coord_diff.y);
	mmap->scale = s;
	mmap->mmapbuf = buf;
}
