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

# define MAP_C_VERTICE 0x005EFF52
# define MAP_C_WALL 0x0020441E
# define MAP_C_PLAYER 0x00F31D3F
# define MAP_C_PLAYERLOOK 0X00B050AB

# define MMAP_C_OUTLINE 0x00444499
# define MMAP_C_VERTICE 0x0090FD88
# define MMAP_C_WALL 0x004A7E48
# define MMAP_C_PLAYER 0x00FF6981
# define MMAP_C_PLAYERLOOK 0X00D598D2

typedef struct s_world {
	t_vert		*verts;
	t_vert		*p_verts;
	t_linedef	*v_walls;
	t_vert		player;
	t_vert		p_angle;
	int			vertcount;
	int			v_wallcount;
	int			w_angle;
}				t_world;

uint32_t	wall_colortable(int i);

long		map_value_to_range(t_range input, t_range output, long value);
uint32_t	map_value_to_buffer(t_range input, uint32_t limit, long value);

t_matrix	init_matrix(void);
t_matrix	rotate_matrix(unsigned char dimension, double angle);
t_matrix	combine_matrices(t_matrix m1, t_matrix m2);
t_matrix	rot_total_matrix(t_matrix m, double x_a, double y_a, double z_a);

t_point		rotate_point(t_point rot_point, t_point pivot_point, int angle);

#endif
