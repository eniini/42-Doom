#include "doom.h"

//ssector 0 = verts 0->1->2->7
//sector 1 = verts 2->4->5->6->7
//sector 2 = 2->3->4
t_debug_room	*init_fake_mapdata(void)
{
	t_debug_room *room;

	room = malloc(sizeof(t_debug_room));
	if (!room)
		ft_getout("failed to init [t_debug_room]");
	room->verts = malloc(sizeof(t_vert) * 8);
	room->walls = malloc(sizeof(t_linedef) * 8);
	if (!room->verts || !room->walls)
		ft_getout("malloc failed for debug room mapdata init");
	//vertices
	room->verts = (t_vert[8]){
		{2 * MAP_UNIT, -4 * MAP_UNIT},
		{4 * MAP_UNIT, 1 * MAP_UNIT},
		{1 * MAP_UNIT, 1 * MAP_UNIT},
		{0 * MAP_UNIT, 4 * MAP_UNIT},
		{-1 * MAP_UNIT, 1 * MAP_UNIT},
		{-4 * MAP_UNIT, 1 * MAP_UNIT},
		{-2 * MAP_UNIT, -4 * MAP_UNIT},
		{0 * MAP_UNIT, -1 * MAP_UNIT}};
	//linedefs
	room->walls = (t_linedef[8]) {
		{room->verts[0], room->verts[1], 0x00b93b3b},
		{room->verts[1], room->verts[2], 0x00b9743b},
		{room->verts[2], room->verts[3], 0x003bb974},
		{room->verts[3], room->verts[4], 0x003bb3b9},
		{room->verts[4], room->verts[5], 0x003b77b9},
		{room->verts[5], room->verts[6], 0x003b3cb9},
		{room->verts[6], room->verts[7], 0x006a3bb9},
		{room->verts[7], room->verts[0], 0x00b93ba8}};
	//room bounding box (= global dimensions)
	room->boundingbox[0] = -4 * MAP_UNIT;
	room->boundingbox[1] = -4 * MAP_UNIT;
	room->boundingbox[2] = 4 * MAP_UNIT;
	room->boundingbox[3] = 4 * MAP_UNIT;
	//unique ceiling & floor height
	room->ceil_h = 8 * MAP_UNIT;
	room->floor_h = 1 * MAP_UNIT;
	//get convex subsectors
	room->subsectors = malloc(sizeof(t_vert *) * 3);
	if (!room->subsectors)
		ft_getout("subsector malloc failed");
	room->subsectors[0] = malloc(sizeof(t_vert) * 4);
	room->subsectors[1] = malloc(sizeof(t_vert) * 5);
	room->subsectors[2] = malloc(sizeof(t_vert) * 3);
	if (!room->subsectors[0] | !room->subsectors[1] | !room->subsectors[2])
		ft_getout("subsector malloc failed");
	//first subsector
	room->subsectors[0][0] = room->verts[0];
	room->subsectors[0][1] = room->verts[1];
	room->subsectors[0][2] = room->verts[2];
	room->subsectors[0][3] = room->verts[7];
	//second subsector
	room->subsectors[1][0] = room->verts[2];
	room->subsectors[1][1] = room->verts[4];
	room->subsectors[1][2] = room->verts[5];
	room->subsectors[1][3] = room->verts[6];
	room->subsectors[1][4] = room->verts[7];
	//third subsector
	room->subsectors[2][0] = room->verts[2];
	room->subsectors[2][1] = room->verts[3];
	room->subsectors[2][2] = room->verts[4];
	//add segs
	room->segs = malloc(sizeof(t_vert) * 8);
	if (!room->segs)
		ft_getout("failed to malloc segs");
	
	return (room);
}
