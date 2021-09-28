#ifndef RENDER_H
# define RENDER_H

# include "defines.h"
# include <limits.h>

/*
*	Similar to Doom, we use the [short] datatype to setup map bounds and the
*	ingame dimensions unit.
*	[32767 / 32 = ~1024] gives the approximate scale of 1 MAP_UNIT = 1m ingame
*	with a max length & width of 1km for a single map.
*	Because coordinate space is rotated and transformed around the player
*	(origin point), total bounding size needs to be exactly mapsize².
*/

# define MAP_UNIT 32
# define BOUND_MIN SHRT_MIN
# define BOUND_MAX SHRT_MAX
# define MAX_MAPSIZE SHRT_MAX

//	Predefined debug colors
# define MAP_C_VERTICE		0xFF5EFF52
# define MAP_C_WALL			0xFF20441E
# define MAP_C_PLAYER		0xFFF31D3F
# define MAP_C_PLAYERLOOK	0XFFB050AB
# define MMAP_C_OUTLINE		0xFF444499
# define MMAP_C_VERTICE		0xFF90FD88
# define MMAP_C_WALL		0xFF4A7E48
# define MMAP_C_PLAYER		0xFFFF6981
# define MMAP_C_PLAYERLOOK	0XFFD598D2

typedef struct s_world {
	t_vert	*verts;
	t_vert	*p_verts;
	t_line	*v_walls;
	t_vert	player;
	t_vert	p_angle;
	int		vertcount;
	int		v_wallcount;
	int		w_angle;
}			t_world;

uint32_t	wall_colortable(int i);

long		map_value_to_range(t_range input, t_range output, long value);
uint32_t	map_value_to_buffer(t_range input, uint32_t limit, long value);

t_vert		rotate_point(t_vert rot_point, t_vert pivot_point, int angle);

#endif
