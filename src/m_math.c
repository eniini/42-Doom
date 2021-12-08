#include "doom.h"

/*
*	Applies a 2d matrix rotation to [rot_point] around the [pivot_point].
*	Since rotation matrix rotates around the origin point, we need to translate
*	to-be-rotated point back to origin, and apply translation back afterwards.
*	Because our Y-axis points down, this rotates clockwise. Reverse rotation
*	can be done with negative [angle] values.
*/
t_ivec3	ivec3_2drotate(t_ivec3 rot_point, t_ivec3 pivot_point, int angle)
{
	t_ivec3	o_rot_result;
	double	c;
	double	s;

	angle = angle % 360;
	c = cos(angle * DEG_TO_RAD);
	s = sin(angle * DEG_TO_RAD);
	rot_point.x -= pivot_point.x;
	rot_point.y -= pivot_point.y;
	o_rot_result.x = (int)round(rot_point.x * c - rot_point.y * s);
	o_rot_result.y = (int)round(rot_point.x * s + rot_point.y * c);
	rot_point.x = o_rot_result.x + pivot_point.x;
	rot_point.y = o_rot_result.y + pivot_point.y;
	rot_point.z = 0;
	return (rot_point);
}

t_vector	vector_2drotate(t_vector rotation_p, t_vector pivot_p, float angle)
{
	t_vector	o_rot_result;
	double		c;
	double		s;

	angle = (int)angle % 360;
	c = cos(angle * DEG_TO_RAD);
	s = sin(angle * DEG_TO_RAD);
	rotation_p.x -= pivot_p.x;
	rotation_p.y -= pivot_p.y;
	o_rot_result.x = round(rotation_p.x * c - rotation_p.y * s);
	o_rot_result.y = round(rotation_p.x * s + rotation_p.y * c);
	rotation_p.x = o_rot_result.x + pivot_p.x;
	rotation_p.y = o_rot_result.y + pivot_p.y;
	rotation_p.z = 0.f;
	rotation_p.w = 1.f;
	return (rotation_p);
}