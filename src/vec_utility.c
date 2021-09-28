#include "doom.h"

/*
*	Calculates the distance between 2d vectors v1 and v2.
*/
float	vector2_dist(t_vector2 v1, t_vector2 v2)
{
	return (sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + \
			((v1.y - v2.y) * (v1.y - v2.y))));
}

/*
*	Vector is normalized i.e. turned into an unit vector, by dividing each of
*	its components by its magnitude.
*/
t_vector2	vector_normalize(t_vector2 v)
{
	t_vector2	ret;
	float		m;

	m = (float)sqrt(v.x * v.x + v.y * v.y);
	ret.x = v.x / m;
	ret.y = v.y / m;
	return (ret);
}
