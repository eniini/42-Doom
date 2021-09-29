#include "doom.h"

/*
*	Returns the addition of points [v1] and [v2].
*/
t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

/*
*	Returns the result of point [v1] substracted by [v2].
*/
t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

/*
*	Returns the result of [v1] divided by the scalar [div].
*/
t_vector	vector_div(t_vector v1, float div)
{
	t_vector	result;

	result.x = v1.x / div;
	result.y = v1.y / div;
	result.z = v1.z / div;
	return (result);
}

/*
*	Returns the result of [p1] multiplied by the scalar [mul].
*/
t_vector	vector_mul(t_vector v1, float mul)
{
	t_vector	result;

	result.x = v1.x * mul;
	result.y = v1.y * mul;
	result.z = v1.z * mul;
	return (result);
}
