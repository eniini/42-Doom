#include "doom.h"

/*
*	!! WIP !! Need to rethink how the minimap should actually function ingame.
*	should be a dynamical sliced view of the map instead of scaling the whole
*	thing. Probably needs Cohen-Sutherland algo to clip map geometry.
*/

static void	do_minimap_line(t_mmap *mm, t_vertex v0, t_vertex v1, uint32_t c)
{
	t_pixel	p0;
	t_pixel	p1;

	p0.x = mm->buf_unit.x * (map_value_to_buffer((t_range){mm->min_coord.x, \
	mm->max_coord.x}, mm->coord_diff.x, v0.x)) / mm->scale + 10;
	p0.y = mm->buf_unit.y * (map_value_to_buffer((t_range){mm->min_coord.y, \
	mm->max_coord.y}, mm->coord_diff.y, v0.y)) / mm->scale + 10;
	p1.x = mm->buf_unit.x * (map_value_to_buffer((t_range){mm->min_coord.x, \
	mm->max_coord.x}, mm->coord_diff.x, v1.x)) / mm->scale + 10;
	p1.y = mm->buf_unit.y * (map_value_to_buffer((t_range){mm->min_coord.y, \
	mm->max_coord.y}, mm->coord_diff.y, v1.y)) / mm->scale + 10;
	draw_line(mm->mmapbuf, p0, p1, c);
}

static void	do_minimap_circle(t_mmap *mm, t_vertex v, int size, uint32_t color)
{
	t_pixel	p;

	p.x = mm->buf_unit.x * map_value_to_buffer((t_range){mm->min_coord.x, \
	mm->max_coord.x}, mm->coord_diff.x, v.x) / mm->scale + 10;
	p.y = mm->buf_unit.y * map_value_to_buffer((t_range){mm->min_coord.y, \
	mm->max_coord.y}, mm->coord_diff.y, v.y) / mm->scale + 10;
	draw_circle(mm->mmapbuf, p, size, color);
}

static void	do_minimap_pixel(t_mmap *mm, t_vertex v, int color)
{
	uint32_t	x;
	uint32_t	y;

	x = map_value_to_buffer((t_range){mm->min_coord.x, mm->max_coord.x}, \
		mm->coord_diff.x, v.x);
	y = map_value_to_buffer((t_range){mm->min_coord.y, mm->max_coord.y}, \
		mm->coord_diff.y, v.y);
	draw_pixel((mm->buf_unit.x * x / mm->scale + 10), (mm->buf_unit.y * \
		y / mm->scale + 10), mm->mmapbuf, color);
}

/*
*	draws scaled outline for minimap
*	then draws the vertexes and linedefs
*	then draw player + lookdir
*/
void	draw_minimap(t_mmap *mm, t_world *world)
{
	int		i;

	i = 0;
	draw_square((t_pixel){0, 0}, \
		(t_pixel){((mm->buf_unit.x * mm->coord_diff.x) / mm->scale) + 20, \
		((mm->buf_unit.y * mm->coord_diff.y) / mm->scale) + 20}, mm->mmapbuf, \
		MMAP_C_OUTLINE);
	draw_square((t_pixel){5, 5}, \
		(t_pixel){((mm->buf_unit.x * mm->coord_diff.x) / mm->scale) + 15, \
		((mm->buf_unit.y * mm->coord_diff.y) / mm->scale) + 15}, mm->mmapbuf, \
		C_BLACK);
	while (i < world->vertcount - 1)
	{
		do_minimap_line(mm, world->verts[i], world->verts[i + 1], \
			wall_colortable(i));
		i++;
	}
	do_minimap_line(mm, world->verts[i], world->verts[0], wall_colortable(i));
	i = 0;
	while (i < world->vertcount)
		do_minimap_pixel(mm, world->verts[i++], MMAP_C_VERTICE);
	do_minimap_circle(mm, world->player, 5, MMAP_C_PLAYER);
	do_minimap_line(mm, world->player, mm->mm_p_angle, MMAP_C_PLAYERLOOK);
}
