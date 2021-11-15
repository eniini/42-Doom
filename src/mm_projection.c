#include "doom.h"

/*
*	Initializes projection matrix for a 3d camera projection.
*	[fov] is camera field of vision in degrees,
*	[ar] is the projection's aspect ratio and
*	near/far are the clipping dimensions of the projection camera.
*/
t_mat4	mm_init_3d_projection(float fov, float ar, float near, float far)
{
	t_mat4	matrix;
	float	fov_rad;

	fov_rad = 1.0f / tanf(fov * 0.5f / 180.f * M_PI);
	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = ar * fov_rad;
	matrix.m[1][1] = fov_rad;
	matrix.m[2][2] = far / (far - near);
	matrix.m[3][2] = (-far * near) / (far - near);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][3] = 0.0f;
	return (matrix);
}
