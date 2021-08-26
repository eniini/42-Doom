#ifndef MAP_H
# define MAP_H

# include <limits.h>

/*
*	MAPDATA LUMP STRUCT
*	byte			mapid
*	signed short	**mapxy //all coords in a single map are indexes in this
*	LINEDEFS	//all the linedefs made in the editor. each LINE points to 
*				one or two SIDEDEFS depending if line is wall or portal
*	SIDEDEF		//defines wall textures and x/y offset
*	SECTOR		//area enclosed with lines, includes lightdata, id for events etc
*	THINGS		//position & angle of monsters, powerups, spawn point etc.
*-------------------------------------------------------------------------------
*	NODES		//BSP data (segs, nodes, subsector leaves)
*	SEGS		//level areas cut with the BSP process
*	SSECTORS	//sets of SEGS that form a convex space
*/

//[32767 / 32 = ~1024] so the map can be 2000 x 2000 units wide max
# define MAP_UNIT 32
# define MAP_MIN SHRT_MIN
# define MAP_MAX SHRT_MAX

# define MAP_C_VERTICE 0x005EFF52
# define MAP_C_WALL 0x0020441E
# define MAP_C_PLAYER 0x00F31D3F
# define MAP_C_PLAYERLOOK 0X00B050AB

# define MMAP_C_OUTLINE 0x00444499
# define MMAP_C_VERTICE 0x0090FD88
# define MMAP_C_WALL 0x004A7E48
# define MMAP_C_PLAYER 0x00FF6981
# define MMAP_C_PLAYERLOOK 0X00D598D2

typedef struct s_vert {
	short	x;
	short	y;
}				t_vert;

typedef struct s_range {
	long	start;
	long	end;
}				t_range;

typedef struct s_world {
	t_vert		*verts;
	int			vertcount;
	t_vert		player;
	t_vert		p_angle;
}				t_world;

long		map_value_to_range(t_range input, t_range output, long value);
uint32_t	map_value_to_buffer(t_range input, uint32_t limit, long value);

#endif