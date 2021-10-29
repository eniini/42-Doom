#include "m_utils.h"

/*
*	Multiplies vector [v] with the matrix [m].
*/
t_vector	mm_multiply_vector(t_vector v, t_mat4 m)
{
	t_vector	ret;

	ret.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] \
	+ v.w * m.m[3][0];
	ret.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] \
	+ v.w * m.m[3][1];
	ret.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] \
	+ v.w * m.m[3][2];
	ret.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] \
	+ v.w * m.m[3][3];
	return (ret);
}

t_mat4	mm_multiply_matrix(t_mat4 ma, t_mat4 mb)
{
	t_mat4	matrix;
	int		column;
	int		row;

	column = 0;
	while (column < 4)
	{
		row = 0;
		while (row < 4)
		{
			matrix.m[row][column] = \
			ma.m[row][0] * mb.m[0][column] + \
			ma.m[row][1] * mb.m[1][column] + \
			ma.m[row][2] * mb.m[2][column] + \
			ma.m[row][3] * mb.m[3][column];
			row++;
		}
		column++;
	}
	return (matrix);
}
