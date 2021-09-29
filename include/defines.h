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
	int	x;
	int	y;
	int	z;
}		t_vector;
typedef t_vector t_vertex;

typedef struct s_fvector {
	float	x;
	float	y;
	float	z;
}			t_fvector;

typedef struct s_pixel {
	uint32_t	x;
	uint32_t	y;
}				t_pixel;

typedef struct s_line {
	t_vector	start;
	t_vector	end;
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
