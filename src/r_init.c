#include "doom.h"

/*
*	Index through the vertices and find the minimum & maximum values included.
*	Returns the distance between min/max X & Y coordinates of a given
*	room/world/space.
*	if [getmax] is TRUE, returns maximum values.
*	Otherwise returns minimum values.
*/
static t_vector	get_mapdimensions(t_world *world, t_bool getmax)
{
	t_vector		*crawler;
	t_vector		max;
	t_vector		min;
	int				i;

	i = 0;
	max = (t_vector){1, 1, 0, 1};
	min = (t_vector){-1, -1, 0, 1};
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

/*
*	In practice, forces projected map dimensions into a square shape.
*/
static void	normalize_coords(t_vector *min, t_vector *max)
{
	if (min->x < min->y)
		min->y = min->x;
	else if (min->y < min->x)
		min->x = min->y;
	if (max->x > max->y)
		max->y = max->x;
	else if (max->y > max->x)
		max->x = max->y;
}

static void	init_world_cont(t_world *world, t_map *map, t_buffer *buf)
{
	int	i;

	i = 0;
	while (i < world->vertcount)
	{
		world->p_verts[i] = world->verts[i];
		i++;
	}
	map->max_coord = get_mapdimensions(world, TRUE);
	map->min_coord = get_mapdimensions(world, FALSE);
	normalize_coords(&map->min_coord, &map->max_coord);
	map->coord_diff.x = map->max_coord.x - map->min_coord.x;
	map->coord_diff.y = map->max_coord.y - map->min_coord.y;
	map->buf_unit.x = ((int)buf->h / map->coord_diff.x);
	map->buf_unit.y = ((int)buf->h / map->coord_diff.y);
	map->mapbuf = buf;
}

void	init_world(t_world *world, t_map *map, t_buffer *buf)
{
	world->w_angle = 0;
	world->player = (t_vector){0, 0, 0, 1};
	world->p_angle = (t_vector){0 * MAP_UNIT, 1 * MAP_UNIT, 0, 1};
	world->vertcount = 8;
	world->verts = malloc(sizeof(t_vertex) * world->vertcount);
	world->p_verts = malloc(sizeof(t_vertex) * world->vertcount);
	world->v_walls = malloc(sizeof(t_line) * (world->vertcount * 2));
	if (!world->v_walls)
		ft_getout("failed to malloc visible wall array!");
	if (!world->verts || !world->p_verts)
		ft_getout("failed to malloc world.verts[]!");
	world->verts[0] = (t_vertex){2 * MAP_UNIT, -4 * MAP_UNIT, 0, 1},
		world->verts[1] = (t_vertex){4 * MAP_UNIT, 1 * MAP_UNIT, 0, 1},
		world->verts[2] = (t_vertex){1 * MAP_UNIT, 1 * MAP_UNIT, 0, 1},
		world->verts[3] = (t_vertex){0 * MAP_UNIT, 4 * MAP_UNIT, 0, 1},
		world->verts[4] = (t_vertex){-1 * MAP_UNIT, 1 * MAP_UNIT, 0, 1},
		world->verts[5] = (t_vertex){-4 * MAP_UNIT, 1 * MAP_UNIT, 0, 1},
		world->verts[6] = (t_vertex){-2 * MAP_UNIT, -4 * MAP_UNIT, 0, 1},
		world->verts[7] = (t_vertex){0 * MAP_UNIT, -1 * MAP_UNIT, 0, 1};
	init_world_cont(world, map, buf);
}

void	init_minimap(t_world *w, t_mmap *mmap, t_buffer *buf, uint32_t s)
{
	mmap->max_coord = get_mapdimensions(w, TRUE);
	mmap->min_coord = get_mapdimensions(w, FALSE);
	normalize_coords(&mmap->min_coord, &mmap->max_coord);
	mmap->coord_diff.x = mmap->max_coord.x - mmap->min_coord.x;
	mmap->coord_diff.y = mmap->max_coord.y - mmap->min_coord.y;
	mmap->buf_unit.x = ((int)buf->h / mmap->coord_diff.x);
	mmap->buf_unit.y = ((int)buf->h / mmap->coord_diff.y);
	mmap->scale = s;
	mmap->mmapbuf = buf;
	mmap->mm_p_angle = w->p_angle;
}
