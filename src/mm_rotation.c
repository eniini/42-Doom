#include "doom.h"

t_mat4	mm_init_rotationmatrix_x(float rad_angle)
{
	t_mat4	matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(rad_angle);
	matrix.m[1][2] = sinf(rad_angle);
	matrix.m[2][1] = -sinf(rad_angle);
	matrix.m[2][2] = cosf(rad_angle);
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

t_mat4	mm_init_rotationmatrix_y(float rad_angle)
{
	t_mat4	matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = cosf(rad_angle);
	matrix.m[0][2] = sinf(rad_angle);
	matrix.m[2][0] = -sinf(rad_angle);
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = cosf(rad_angle);
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

t_mat4	mm_init_rotationmatrix_z(float rad_angle)
{
	t_mat4	matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = cosf(rad_angle);
	matrix.m[0][1] = sinf(rad_angle);
	matrix.m[1][0] = -sinf(rad_angle);
	matrix.m[1][1] = cosf(rad_angle);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return (matrix);
}
