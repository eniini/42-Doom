#include "doom.h"

static void	convex_room_setup(t_dbg_room *room)
{
	int	i;

	room->vertices = (t_vertex[5]){
	{2 * MAP_UNIT, -2 * MAP_UNIT, 0},
	{2 * MAP_UNIT, 2 * MAP_UNIT, 0},
	{-2 * MAP_UNIT, 3 * MAP_UNIT, 0},
	{-4 * MAP_UNIT, 0 * MAP_UNIT, 0},
	{-2 * MAP_UNIT, -3 * MAP_UNIT, 0}};
	i = 0;
	while (i < room->wallcount - 1)
	{
		room->walls[i].start = room->vertices[i];
		room->walls[i].end = room->vertices[i + 1];
		room->walls[i].color = wall_colortable(i);
		i++;
	}
	room->walls[i].start = room->vertices[i];
	room->walls[i].end = room->vertices[0];
	room->walls[i].color = wall_colortable(i);
}

/*
*	Initializes a convex-shaped room data.
*	Consists of 5 vertices creating 5 walls.
*/
t_dbg_room	*init_convex_room(void)
{
	t_dbg_room	*room;

	room = malloc(sizeof(t_dbg_room));
	if (!room)
		ft_getout("failed to init [t_debug_room]");
	room->wallcount = 5;
	room->vertices = malloc(sizeof(t_vertex) * room->wallcount);
	room->walls = malloc(sizeof(t_line) * room->wallcount);
	if (!room->vertices || !room->walls)
		ft_getout("malloc failed for debug room mapdata init");
	convex_room_setup(room);
	room->boundingbox[0] = -3 * MAP_UNIT;
	room->boundingbox[1] = -4 * MAP_UNIT;
	room->boundingbox[2] = 3 * MAP_UNIT;
	room->boundingbox[3] = 2 * MAP_UNIT;
	room->ceil_h = 8 * MAP_UNIT;
	room->floor_h = 1 * MAP_UNIT;
	return (room);
}

/*
*****************************************************************************/

static void	nonconvex_room_setup(t_dbg_room *room)
{
	int	i;

	room->vertices = (t_vertex[8]){
	{2 * MAP_UNIT, -4 * MAP_UNIT, 0},
	{4 * MAP_UNIT, 1 * MAP_UNIT, 0},
	{1 * MAP_UNIT, 1 * MAP_UNIT, 0},
	{0 * MAP_UNIT, 4 * MAP_UNIT, 0},
	{-1 * MAP_UNIT, 1 * MAP_UNIT, 0},
	{-4 * MAP_UNIT, 1 * MAP_UNIT, 0},
	{-2 * MAP_UNIT, -4 * MAP_UNIT, 0},
	{0 * MAP_UNIT, -1 * MAP_UNIT, 0}};
	i = 0;
	while (i < room->wallcount - 1)
	{
		room->walls[i].start = room->vertices[i];
		room->walls[i].end = room->vertices[i + 1];
		room->walls[i].color = wall_colortable(i);
		i++;
	}
	room->walls[i].start = room->vertices[i];
	room->walls[i].end = room->vertices[0];
	room->walls[i].color = wall_colortable(i);
}

/*
*	Initializes a nonconvex-shaped room with 8 vertices & 8 walls.
*/
t_dbg_room	*init_nonconvex_room(void)
{
	t_dbg_room	*room;

	room = malloc(sizeof(t_dbg_room));
	if (!room)
		ft_getout("failed to init [t_debug_room]");
	room->wallcount = 8;
	room->vertices = malloc(sizeof(t_vertex) * room->wallcount);
	room->walls = malloc(sizeof(t_line) * room->wallcount);
	if (!room->vertices || !room->walls)
		ft_getout("malloc failed for debug room mapdata init");
	nonconvex_room_setup(room);
	room->boundingbox[0] = -4 * MAP_UNIT;
	room->boundingbox[1] = -4 * MAP_UNIT;
	room->boundingbox[2] = 4 * MAP_UNIT;
	room->boundingbox[3] = 4 * MAP_UNIT;
	room->ceil_h = 8 * MAP_UNIT;
	room->floor_h = 1 * MAP_UNIT;
	return (room);
}
