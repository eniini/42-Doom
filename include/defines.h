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

typedef struct s_point2 {
	int	x;
	int	y;
}		t_point2;
typedef t_point2 t_vert;

typedef struct s_point3 {
	int	x;
	int	y;
	int	z;
}		t_point3;

typedef struct s_line {
	t_point2	start;
	t_point2	end;
	uint32_t	color;
}				t_line;

//Handles mapping signed/unsigned ints into a range.
typedef struct s_range {
	long	start;
	long	end;
}			t_range;
//floating-point 2d unit. Used to represent velocity & orientation.
typedef struct s_vector2 {
	float	x;
	float	y;
}			t_vector2;
//floating-point 3d unit. Used to simulate 3D physics.
typedef struct s_vector3 {
	float	x;
	float	y;
	float	z;
}			t_vector3;
//Datatype to store an ARBG image. Each pixel can be found by calculating
//[(h * y) + (x % w)]
typedef struct s_img {
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_img;
typedef t_img	t_buffer;

#endif
