#include "doom.h"

/*
*	Calculates the distance between 2d vectors v1 and v2.
*/
float	vector2_dist(t_vector v1, t_vector v2)
{
	return (sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + \
			((v1.y - v2.y) * (v1.y - v2.y))));
}

/*
*	Vector is normalized i.e. turned into an unit vector, by dividing each of
*	its components by its magnitude.
*/
t_vector	vector2_normalize(t_vector v)
{
	t_vector	ret;
	float		m;

	m = (float)sqrt(v.x * v.x + v.y * v.y);
	ret.x = v.x / m;
	ret.y = v.y / m;
	return (ret);
}

/*
*	Dot product (a · b) returns a scalar that respresents how much the two
*	vectors are 'alike'. In practice, return value
*	[< 0] means that the angle between two vectors is more than 90°,
*	[0] means that the angle is exactly 90° and
*	[> 0] means that the angle is less than 90°.
*/
int	vector2_dotproduct(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

/*
*	Returns a magnitude of an perpendicular vector to the plane (v1, v2).
*/
int	vector2_crossproduct(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.y) - (v2.x * v1.y));
}

/*
*	We're checking if a vector from [wall.start] to [point] is
*	in front of [wall]. 'In front of' in this relation means clockwise
*	from the starting point.
*/
t_bool	front_of_line(t_line wall, t_vector point)
{
	t_vector	wallvector;
	t_vector	pointvector;

	pointvector = vector_sub(wall.end, wall.start);
	wallvector = vector_sub(point, wall.start);
	if (vector2_crossproduct(wallvector, pointvector) > 0)
		return (TRUE);
	return (FALSE);
}