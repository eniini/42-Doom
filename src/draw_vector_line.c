#include "doom.h"

/*
*	Initializes outcodes for Cohen-Sutherland-styled clipping of an
*	integer vector into unsigned buffer space.
*	INSIDE	0	[0000]
*	LEFT	1	[0001]
*	RIGHT	2	[0010]
*	BOTTOM	4	[0100]
*	TOP		8	[1000]
*
*	1001 | 1000 | 1010
*	-----+------+-----
*	0001 | 0000 | 0010
*	-----+------+-----
*	0101 | 0100 | 0110
*/
static int	get_ocode(t_buffer *buf, t_vector v)
{
	int	outcode;

	outcode = 0;
	if (v.x < 0)
		outcode |= 1;
	else if (v.x > (int)buf->w)
		outcode |= 2;
	if (v.y < 0)
		outcode |= 4;
	else if (v.y > (int)buf->h)
		outcode |= 8;
	return (outcode);
}

/*
*	Finds the screen-space intersection point between [o] and [e].
*/
static t_vector	line_clip(t_buffer *buf, t_vector v0, t_vector v1, int ocode)
{
	t_vector	rv;

	if (ocode & 8)
	{
		rv.x = v0.x + (v1.x - v0.x) * ((int)buf->h - v0.y) / (v1.y - v0.y);
		rv.y = (int)buf->h;
	}
	else if (ocode & 4)
	{
		rv.x = v0.x + (v1.x - v0.x) * -v0.y / (v1.y - v0.y);
		rv.y = 0;
	}
	else if (ocode & 2)
	{
		rv.y = v0.y + (v1.y - v0.y) * ((int)buf->w - v0.x) / (v1.x - v0.x);
		rv.x = (int)buf->w;
	}
	else if (ocode & 1)
	{
		ft_printf("%d | %d\n", v1.x, v0.x);
		rv.y = v0.y + (v1.y - v0.y) * -v0.x / (v1.x - v0.x);
		rv.x = 0;
	}
	return (rv);
}

/*
*	Note: Outcodes are stored as a single vector where
*	[ocodes.x] = start,
*	[ocodes.y] = end,
*	[ocodes.z] = out.
*/

/*
*	Handling line clipping in unsigned buffer space  using Cohen-Sutherland alg.
*	Lines with both vectors outside the drawing area are ignored - other
*	functions should handle that.
*/
void	draw_vector_line(t_buffer *buf, t_line line, uint32_t c)
{
	t_vector	ocode;

	ocode = (t_vector){get_ocode(buf, line.start), get_ocode(buf, line.end), 0};
	while (TRUE)
	{
		if (ocode.x & ocode.y)
			return ;
		if (!(ocode.x | ocode.y))
			return (draw_line(buf, (t_pixel){line.start.x, line.start.y}, \
				(t_pixel){line.end.x, line.end.y}, c));
		if (ocode.y > ocode.x)
			ocode.z = ocode.y;
		else
			ocode.z = ocode.x;
		if (ocode.z == ocode.x)
		{
			line.start = line_clip(buf, line.start, line.end, ocode.z);
			ocode.x = get_ocode(buf, line.start);
		}
		else
		{
			line.end = line_clip(buf, line.start, line.end, ocode.z);
			ocode.y = get_ocode(buf, line.end);
		}
	}
}
