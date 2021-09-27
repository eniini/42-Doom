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

//Memory representation of a point in a map.
typedef struct s_vert {
	int	x;
	int	y;
}		t_vert;

//Projection/Matrix datatype
typedef struct s_3dvert {
	int	x;
	int	y;
	int	z;
}		t_3dvert;

//Memory representation of a line in a map.
typedef struct s_linedef {
	t_vert		start;
	t_vert		end;
	uint32_t	color;
}				t_linedef;

//Handles mapping integer values into a range.
typedef struct s_range {
	long	start;
	long	end;
}			t_range;

//Datatype for handling buffer/array coordinates
typedef struct s_point {
	uint32_t	x;
	uint32_t	y;
}				t_point;

typedef struct s_f_point {
	float	x;
	float	y;
}			t_f_point;

//datatype to store an ARBG image. Each pixel can be found by calculating
//[(h * y) + (x % w)]
typedef struct s_imgdata {
	uint32_t	*data;
	uint32_t	w;
	uint32_t	h;
}				t_imgdata;

//TODO: maybe do typedef s_imgdata t_buffer ?
typedef struct s_buffer {
	uint32_t	*pixels;
	uint32_t	w;
	uint32_t	h;
}				t_buffer;

//its a mistake to handle any math with unsigned values
//leave <=0 checks to buffer submodule!
typedef struct s_matrix {
	double	m[4][4];
}			t_matrix;

#endif
