#include "doom.h"

/*
*	Returns the addition of vectors [v1] and [v2].
*/
t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return (v);
}

/*
*	Returns the result of vector [v1] substracted by [v2].
*/
t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return (v);
}

/*
*	Returns the result of [v1] divided by the scalar [div].
*/
t_vector	vector_div(t_vector v1, float div)
{
	t_vector	v;

	v.x = v1.x / div;
	v.y = v1.y / div;
	return (v);
}

/*
*	Returns the result of [v1] multiplied by the scalar [mul].
*/
t_vector	vector_mul(t_vector v1, float mul)
{
	t_vector	v;

	v.x = v1.x * mul;
	v.y = v1.y * mul;
	return (v);
}
