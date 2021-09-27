#include "doom.h"

void	check_bounds(t_vert vert)
{
	if (vert.x > BOUND_MAX)
		vert.x = BOUND_MAX;
	else if (vert.x < BOUND_MIN)
		vert.x = BOUND_MIN;
	if (vert.y > BOUND_MAX)
		vert.y = BOUND_MAX;
	else if (vert.y < BOUND_MIN)
		vert.y = BOUND_MIN;
}

void	apply_movement(t_world *world, t_vert direction)
{
	int	i;

	i = 0;
	while (i < world->vertcount)
	{
		world->p_verts[i].x += direction.x;
		world->p_verts[i].y += direction.y;
		check_bounds(world->p_verts[i]);
		world->verts[i].x += direction.x;
		world->verts[i].y += direction.y;
		check_bounds(world->verts[i]);
		i++;
	}
}
