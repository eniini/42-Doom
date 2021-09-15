#include "doom.h"

/*
*	Debug colortable
*/
uint32_t	wall_colortable(int i)
{
	static uint32_t	colortable[8] = {
	0x00b93b3b,
	0x00b9743b,
	0x003bb974,
	0x003bb3b9,
	0x003b77b9,
	0x003b3cb9,
	0x006a3bb9,
	0x00b93ba8};

	if (i < 8)
		return (colortable[i]);
	return (0x00000000);
}

/*
*	Translate coordinates into buffer.
*/
static void	draw_buffer_line(t_map *map, t_vert start, t_vert end, uint32_t c)
{
	draw_line(map->mapbuf, \
		(t_point){map->mapbuf->w / 2 + map->buf_unit.x * start.x,
		map->mapbuf->h / 2 + map->buf_unit.y * start.y}, \
		(t_point){map->mapbuf->w / 2 + map->buf_unit.x * end.x, \
		map->mapbuf->h / 2 + map->buf_unit.y * end.y}, c);
}

/*
*	Draws only what is visible to the player of the currently loaded mapdata.
*/
void	draw_visibleverts(t_map *map, t_world *world)
{
	int		i;

	i = 0;
	while (i < world->v_wallcount)
	{
		draw_buffer_line(map, world->v_walls[i].start, world->v_walls[i].end, \
			world->v_walls[i].color);
		i++;
	}
}

/*
*	Draws all the loaded mapdata.
*/
void	draw_map(t_map *map, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->vertcount - 1)
	{
		draw_buffer_line(map, world->p_verts[i], world->p_verts[i + 1],
			wall_colortable(i));
		i++;
	}
	draw_buffer_line(map, world->p_verts[i], world->p_verts[0],
		wall_colortable(i));
	i = 0;
	draw_buffer_line(map, (t_vert){0, 0}, world->p_angle, MMAP_C_PLAYERLOOK);
	draw_circle(map->mapbuf, (t_point){map->mapbuf->w / 2, map->mapbuf->h / 2},
		10, MMAP_C_PLAYER);
}
