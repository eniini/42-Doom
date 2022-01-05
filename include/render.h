#ifndef RENDER_H
# define RENDER_H

# include "defines.h"
# include <limits.h>

# define C_OCHRE	0xffbc8650
# define C_BRICK 	0xffbc5050
# define C_LEMON	0xffbcbc50
# define C_LIME		0xff86bc50
# define C_GRASS	0xff50bc50
# define C_MINT		0xff50bc86
# define C_ICE		0xff50bcb7
# define C_SKY		0xff508bbc
# define C_AZURE	0xff5055bc
# define C_GRAPE	0xff8150bc
# define C_CHERRY	0xffbc5080
# define C_PLUM		0xffFF5733

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

/*
*	Bounding box data is [ymin, xmin, ymax, xmax]
*/
typedef struct s_room {
	int			wallcount;
	t_vertex	*vertices;
	t_wall		*walls;
	t_wall		*proj_walls;
	short		boundingbox[4];
	short		ceil_h;
	short		floor_h;
}				t_room;

t_room	*init_convex_room(int i);
t_room	*init_nonconvex_room(void);

typedef struct s_world {
	//legacy stuff
	t_vertex	*verts;
	t_vertex	*p_verts;
	t_wall		*v_walls;
	t_vector	player;
	t_vector	p_angle;
	int			vertcount;
	int			v_wallcount;
	int			w_angle;
	//active stuff below!
	t_tri		*cube;
	t_mat4		m_proj;
	t_vector	camera;
	int			tricount;
	t_vector	cube_rotation;
	float		cam_distance;
	float		cam_fov;
	//current version of the active room (which walls are drawn)
	t_room		*room[2];
	int			room_count;
	int			player_angle;
	int			player_rotation;
}				t_world;

uint32_t	wall_colortable(int i);

long		map_value_to_range(t_range input, t_range output, long value);
uint32_t	map_value_to_buffer(t_range input, uint32_t limit, long value);

t_ivec3		ivec3_2drotate(t_ivec3 rot_point, t_ivec3 pivot_point, int angle);
t_vector	vector_2drotate(t_vector rotation_p, t_vector pivot_p, float angle);

#endif
