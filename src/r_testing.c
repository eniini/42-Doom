#include "doom.h"

/*
*	Render wall segments, sorted front to back from player's POV.
*	Both wall ends are projected into screen-space x-axis. Based
*	on distance and floor/ceiling height, calculate each column
*	y-offset and height. (same kind of column drawing as with wolf3d).
*/

//func to check which side of the wall is visible

/*
*	Project wall verts into screen space coords
*	Texture coord [u] is generated for each column,
*	lerp(screenspace wall width, column x)
*/

void	r_dotests(t_rend *rend, t_world *w)
{
	
}