#include "doom.h"

t_mat4	mm_init_unitmatrix(void)
{
	return ((t_mat4){{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}}});
}

t_mat4	mm_init_translation(float x, float y, float z)
{
	return ((t_mat4){{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{x, y, z, 1}}});
}
