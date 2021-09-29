#include "doom.h"

/*
*	Applies a 2d matrix rotation to [rot_point] around the [pivot_point].
*	Since rotation matrix rotates around the origin point, we need to translate
*	to-be-rotated point back to origin, and apply translation back afterwards.
*	Because our Y-axis points down, this rotates clockwise. Reverse rotation
*	can be done with negative [angle] values.
*/
t_vector	vector2_rotate(t_vector rot_point, t_vector pivot_point, int angle)
{
	t_vector	o_rot_result;
	double		c;
	double		s;

	angle = angle % 360;
	c = cos(angle * DEG_TO_RAD);
	s = sin(angle * DEG_TO_RAD);
	rot_point.x -= pivot_point.x;
	rot_point.y -= pivot_point.y;
	o_rot_result.x = (int)round(rot_point.x * c - rot_point.y * s);
	o_rot_result.y = (int)round(rot_point.x * s + rot_point.y * c);
	rot_point.x = o_rot_result.x + pivot_point.x;
	rot_point.y = o_rot_result.y + pivot_point.y;
	return (rot_point);
}
