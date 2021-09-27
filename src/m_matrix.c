#include "doom.h"

t_matrix	init_matrix(void)
{
	return ((t_matrix){{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}}});
}

/*
*	[Dimension] is one of [x],[y] or [z].
*/
t_matrix	rotate_matrix(unsigned char dimension, double angle)
{
	if (dimension == 'x')
	{
		return ((t_matrix){.m[0][0] = 1, .m[0][1] = 0, .m[0][2] = 0,
			.m[0][3] = 0, .m[1][0] = 0, .m[1][1] = cos(angle),
			.m[1][2] = sin(angle), .m[1][3] = 0, .m[2][0] = 0,
			.m[2][1] = -sin(angle), .m[2][2] = cos(angle), .m[2][3] = 0,
			.m[3][0] = 0, .m[3][1] = 0, .m[3][2] = 0, .m[3][3] = 1});
	}
	else if (dimension == 'y')
	{
		return ((t_matrix){.m[0][0] = cos(angle), .m[0][1] = 0,
			.m[0][2] = -sin(angle), .m[0][3] = 0, .m[1][0] = 0, .m[1][1] = 1,
			.m[1][2] = 0, .m[1][3] = 0, .m[2][0] = sin(angle),
			.m[2][1] = 0, .m[2][2] = cos(angle), .m[2][3] = 0,
			.m[3][0] = 0, .m[3][1] = 0, .m[3][2] = 0, .m[3][3] = 1});
	}
	else if (dimension == 'z')
		return ((t_matrix){.m[0][0] = cos(angle), .m[0][1] = sin(angle),
			.m[0][2] = 0, .m[0][3] = 0, .m[1][0] = -sin(angle),
			.m[1][1] = cos(angle), .m[1][2] = 0, .m[1][3] = 0,
			.m[2][0] = 0, .m[2][1] = 0, .m[2][2] = 1, .m[2][3] = 0,
			.m[3][0] = 0, .m[3][1] = 0, .m[3][2] = 0, .m[3][3] = 1});
	else
		return (init_matrix());
}

/*
*	Combining two matrices means that each cell equals the sum of rows
*	multiplied by columns.
*/
t_matrix	combine_matrices(t_matrix m1, t_matrix m2)
{
	int			i;
	int			j;
	t_matrix	combo;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			combo.m[i][j] = m1.m[0][j] * m2.m[i][0] + \
							m1.m[1][j] * m2.m[i][1] + \
							m1.m[2][j] * m2.m[i][2] + \
							m1.m[3][j] * m2.m[i][3];
			j++;
		}
		i++;
	}
	return (combo);
}

t_matrix	rot_total_matrix(t_matrix m, double x_a, double y_a, double z_a)
{
	t_matrix	ret;
	t_matrix	x_rot;
	t_matrix	y_rot;
	t_matrix	z_rot;

	x_rot = rotate_matrix('x', x_a);
	y_rot = rotate_matrix('y', y_a);
	z_rot = rotate_matrix('z', z_a);
	ret = combine_matrices(z_rot, combine_matrices(x_rot, y_rot));
	return (combine_matrices(m, ret));
}
