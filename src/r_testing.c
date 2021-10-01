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

/*
*	Translate coordinates into buffer.
*/
static void	draw_buffer_line(t_buffer *b, t_line wall, short *bbox)
{
	t_pixel start;
	t_pixel end;

	start.x = map_value_to_buffer((t_range){bbox[1], bbox[3]}, \
		b->w, wall.start.x);
	start.y = map_value_to_buffer((t_range){bbox[0], bbox[2]}, \
		b->h, wall.start.y);
	end.x = map_value_to_buffer((t_range){bbox[1], bbox[3]}, \
		b->w, wall.end.x);
	end.y = map_value_to_buffer((t_range){bbox[0], bbox[2]}, \
		b->h, wall.end.y);
	draw_line(b, start, end, wall.color);
}

/*
*	Draws only what is visible to the player of the currently loaded mapdata.
*/
static void	draw_room2d(t_buffer *buf, t_dbg_room *room)
{
	int		i;

	i = 0;
	while (i < room->wallcount)
	{
		draw_buffer_line(buf, room->walls[i], room->boundingbox);
		i++;
	}
}

int	rotation = 0;
t_vertex	sp = (t_vertex){-WIN_W, -WIN_H, 0};
static t_vertex pivot = (t_vertex){WIN_W / 2, WIN_H / 2, 0};

void	r_dotests(t_rend *rend, t_dbg_room *room)
{
	t_vertex	v;
	t_pixel		px1;
	t_pixel		px2;
	t_line		line;

	rotation++;
	v = vector2_rotate(sp, pivot, rotation);
	line.start = v;
	line.end = pivot;
	line.color = 0xff66a644;
	draw_vector_line(rend->win_buffer, line, 0xffaabbcc);
	/*
	px1.x = v.x;
	px1.y = v.y;
	px2.x = pivot.x;
	px2.y = pivot.y;
	draw_line(rend->win_buffer, px2, px1, 0xffaabbcc);
	*/
	//draw_room2d(rend->win_buffer, room);
}
