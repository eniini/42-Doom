#include "doom.h"

/*
*	Colors the pixel in given coordinates of the given buffer as the given
*	hexadecimal value [0xAARRGGBB]. (00 for AA being zero transparency)
*/
void	drawpixel(uint32_t x, uint32_t y, t_buffer *buffer, uint32_t color)
{
	uint32_t	i;

	i = (buffer->w * y) + x;
	if (x < buffer->w && y < buffer->h)
		buffer->pixels[i] = color;
}

/******************************************************************************/
//	Initializing bunch of values in separate functions to appease Norminette.
//	Otherwise pixel-accurate line drawing algorithm between 2 point coordinates.
//	Initial checks make sure that drawing works for all angles into
//	every direction. After that, drawline() plots
//	a line of pixels from [point0] to [point1].
/******************************************************************************/

static t_point	init_startingvalues(t_point p0, t_point p1, t_bool flip)
{
	t_point	abs_startval;

	abs_startval.x = p0.x;
	abs_startval.y = p0.y;
	return (abs_startval);
}

static void	init_errors(t_point p0, t_point p1, int *derror, int *error)
{
	*derror = abs(p1.y - p0.y) * 2;
	*error = 0;
}

static t_bool	init_points(t_point *p0, t_point *p1)
{
	t_bool	flip;

	flip = FALSE;
	if (abs(p0->x - p1->x) < abs(p0->y - p1->y))
	{
		ft_swap(&p0->x, &p0->y, sizeof(int));
		ft_swap(&p1->x, &p1->y, sizeof(int));
		flip = TRUE;
	}
	if (p0->x > p1->x)
	{
		ft_swap(&p0->x, &p1->x, sizeof(int));
		ft_swap(&p0->y, &p1->y, sizeof(int));
	}
	return (flip);
}

/*
*	Bresenham's line algorithm.
*/
void	draw_line(t_buffer *buf, t_point p0, t_point p1, uint32_t color)
{
	int		derror;
	int		error;
	t_point	crawler;
	t_bool	flip;

	flip = init_points(&p0, &p1);
	crawler = init_startingvalues(p0, p1, flip);
	init_errors(p0, p1, &derror, &error);
	while (crawler.x <= p1.x)
	{
		if (!flip)
			drawpixel(crawler.x++, crawler.y, buf, color);
		else
			drawpixel(crawler.y, crawler.x++, buf, color);
		error += derror;
		if (error > p1.x - p0.x)
		{
			if (p1.y > p0.y)
				crawler.y += 1;
			else
				crawler.y += -1;
			error -= (p1.x - p0.x) * 2;
		}
	}
}

/*
*	Calculates points on the border of the circle in its first octant,
*	rest are determined by symmetry. draw unique points until (x = y)
*	choosing points closest to the radius of the circle.
*/
void	draw_circle(t_buffer *buf, t_point p, int r, uint32_t color)
{
	int	x;
	int	y;
	int	d;

	x = r;
	y = 0;
	d = 1 - r;
	while (x >= y)
	{
		drawpixel(p.x + x, p.y + y, buf, color);
		drawpixel(p.x - x, p.y + y, buf, color);
		drawpixel(p.x + x, p.y - y, buf, color);
		drawpixel(p.x - x, p.y - y, buf, color);
		drawpixel(p.x + y, p.y + x, buf, color);
		drawpixel(p.x - y, p.y + x, buf, color);
		drawpixel(p.x + y, p.y - x, buf, color);
		drawpixel(p.x - y, p.y - x, buf, color);
		if (d < 0)
			d += (2 * ++y) + 1;
		else
		{
			x--;
			d += (2 * (++y - x)) + 1;
		}
	}
}

/*
*	Instead of drawing individual pixels on symmetrical positions along the
*	circle's radius, we draw lines from one end to its opposite.
*/
void	draw_filled_circle(t_buffer *buf, t_point p, int r, uint32_t color)
{
	int	x;
	int	y;
	int	d;

	x = r;
	y = 0;
	d = 1 - r;
	while (x >= y)
	{
		draw_line(buf, (t_point){p.x + x, p.y + y},
			(t_point){p.x - x, p.y + y}, color);
		draw_line(buf, (t_point){p.x + x, p.y - y},
			(t_point){p.x - x, p.y - y}, color);
		draw_line(buf, (t_point){p.x + y, p.y + x},
			(t_point){p.x - y, p.y + x}, color);
		draw_line(buf, (t_point){p.x + y, p.y - x},
			(t_point){p.x - y, p.y - x}, color);
		if (d < 0)
			d += (2 * ++y) + 1;
		else
		{
			x--;
			d += (2 * (++y - x)) + 1;
		}
	}
}
