#include "doom.h"

/*
*	Clamps vertex position inside the min/max map coordinates.
*/
void	check_bounds(t_vertex vertex)
{
	if (vertex.x > BOUND_MAX)
		vertex.x = BOUND_MAX;
	else if (vertex.x < BOUND_MIN)
		vertex.x = BOUND_MIN;
	if (vertex.y > BOUND_MAX)
		vertex.y = BOUND_MAX;
	else if (vertex.y < BOUND_MIN)
		vertex.y = BOUND_MIN;
}

/*
*	Increments map geometry in relation to player position (origin point).
*/
void	apply_movement(t_world *world, t_vector direction)
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
