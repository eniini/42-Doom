#include "doom.h"

static void	convex_room_setup(t_dbg_room *room)
{
	int i;

	room->verts = (t_vert[5]){
	{2 * MAP_UNIT, -2 * MAP_UNIT},
	{2 * MAP_UNIT, 2 * MAP_UNIT},
	{-2 * MAP_UNIT, 3 * MAP_UNIT},
	{-4 * MAP_UNIT, 0 * MAP_UNIT},
	{-2 * MAP_UNIT, -3 * MAP_UNIT}};
	i = 0;
	while (i < room->wallcount - 1)
	{
		room->walls[i].start = room->verts[i];
		room->walls[i].end = room->verts[i + 1];
		i++;
	}
	room->walls[i].start = room->verts[i];
	room->walls[i].end = room->verts[0];
	room->walls[0].color = 0x00b93b3b;
	room->walls[1].color = 0x00b9743b;
	room->walls[2].color = 0x003bb974;
	room->walls[3].color = 0x003bb3b9;
	room->walls[4].color = 0x003b77b9;
}

t_dbg_room	*init_convex_room(void)
{
	t_dbg_room	*room;

	room = malloc(sizeof(t_dbg_room));
	if (!room)
		ft_getout("failed to init [t_debug_room]");
	room->wallcount = 5;
	room->verts = malloc(sizeof(t_vert) * room->wallcount);
	room->walls = malloc(sizeof(t_linedef) * room->wallcount);
	if (!room->verts || !room->walls)
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

static void	nonconvex_room_setup(t_dbg_room *room)
{
	room->verts = (t_vert[8]){
	{2 * MAP_UNIT, -4 * MAP_UNIT},
	{4 * MAP_UNIT, 1 * MAP_UNIT},
	{1 * MAP_UNIT, 1 * MAP_UNIT},
	{0 * MAP_UNIT, 4 * MAP_UNIT},
	{-1 * MAP_UNIT, 1 * MAP_UNIT},
	{-4 * MAP_UNIT, 1 * MAP_UNIT},
	{-2 * MAP_UNIT, -4 * MAP_UNIT},
	{0 * MAP_UNIT, -1 * MAP_UNIT}};
	room->walls = (t_linedef[8]){
	{room->verts[0], room->verts[1], 0x00b93b3b},
	{room->verts[1], room->verts[2], 0x00b9743b},
	{room->verts[2], room->verts[3], 0x003bb974},
	{room->verts[3], room->verts[4], 0x003bb3b9},
	{room->verts[4], room->verts[5], 0x003b77b9},
	{room->verts[5], room->verts[6], 0x003b3cb9},
	{room->verts[6], room->verts[7], 0x006a3bb9},
	{room->verts[7], room->verts[0], 0x00b93ba8}};
}

t_dbg_room	*init_nonconvex_room(void)
{
	t_dbg_room	*room;

	room = malloc(sizeof(t_dbg_room));
	if (!room)
		ft_getout("failed to init [t_debug_room]");
	room->wallcount = 8;
	room->verts = malloc(sizeof(t_vert) * room->wallcount);
	room->walls = malloc(sizeof(t_linedef) * room->wallcount);
	if (!room->verts || !room->walls)
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
