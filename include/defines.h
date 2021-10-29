#ifndef DEFINES_H
# define DEFINES_H

# include <stdint.h>

/*
*	Defines a bunch of generic/specialized datatypes for use within multiple
*	areas of the program.
*/

//Predefined angles for player-independent object orientation
# define ANGLE_E	0
# define ANGLE_NE	45
# define ANGLE_N	90
# define ANGLE_NW	135
# define ANGLE_W	180
# define ANGLE_SW	225
# define ANGLE_S	270
# define ANGLE_SE	315

typedef struct s_vector {
	float	x;
	float	y;
	float	z;
	float	w;
}			t_vector;
typedef t_vector t_vertex;
typedef t_vector t_fvector;

//base unit for 3d projection
typedef struct s_tri {
	t_vector	p[3];
}				t_tri;
//base unit for map geometry
typedef struct s_wall {
	t_vector	start;
	t_vector	end;
	uint32_t	color;
}				t_wall;
//4 x 4 matrix
typedef struct s_mat4 {
	float	m[4][4];
}			t_mat4;

typedef struct s_pixel {
	uint32_t	x;
	uint32_t	y;
}				t_pixel;

typedef struct s_ivec3 {
	int		x;
	int		y;
	int		z;
}			t_ivec3;
//integer-based line drawing stuct
typedef struct s_line {
	t_ivec3		start;
	t_ivec3		end;
	uint32_t	color;
}				t_line;
//Handles mapping signed/unsigned ints into a range.
typedef struct s_range {
	long	start;
	long	end;
}			t_range;
//Datatype to store an ARBG image. Each pixel can be found by calculating
//[(h * y) + (x % w)]
typedef struct s_img {
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_img;
typedef t_img	t_buffer;

#endif
