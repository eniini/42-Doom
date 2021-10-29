#include "m_utils.h"

t_vector	mv_add(t_vector va, t_vector vb)
{
	t_vector	vector;

	vector.x = va.x + vb.x;
	vector.y = va.y + vb.y;
	vector.z = va.z + vb.z;
	return (vector);
}

t_vector	mv_substract(t_vector va, t_vector vb)
{
	t_vector	vector;

	vector.x = va.x - vb.x;
	vector.y = va.y - vb.y;
	vector.z = va.z - vb.z;
	return (vector);
}

t_vector	mv_multiply(t_vector v, float multiplier)
{
	t_vector	vector;

	vector.x = v.x * multiplier;
	vector.y = v.y * multiplier;
	vector.z = v.z * multiplier;
	return (vector);
}

t_vector	mv_divide(t_vector v, float divisor)
{
	t_vector	vector;

	vector.x = v.x / divisor;
	vector.y = v.y / divisor;
	vector.z = v.z / divisor;
	return (vector);
}
