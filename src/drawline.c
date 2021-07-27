#include "doom.h"

//****************************************************************************//
//linedraw testing
t_point	p0 = {1, 1};
t_point	p1 = {1, 600};
t_point	p2 = {800, 1};
float	counter = 0.0;
t_bool	flag = FALSE;

/*
*	linedraw testing
*/
void	drawlinetest(t_rend *r)
{
	static t_point	mp0;

	mp0.x = ft_i_lerp(p1.x, p2.x, counter);
	mp0.y = ft_i_lerp(p1.y, p2.y, counter);
	if (!flag)
	{
		counter += 0.001;
		if (counter >= 1.0)
			flag = TRUE;
	}
	if (flag)
	{
		counter -= 0.001;
		if (counter <= 0.0)
			flag = FALSE;
	}
	draw_line(r, p0, mp0, ft_color_lerp(0x006666ff, 0x00ff6666, counter));
}
//****************************************************************************//
//real functions

void	drawpixel(int x, int y, t_rend *r, uint32_t color)
{
	uint32_t	i;

	i = (WIN_W * y) + x;
	if (x < WIN_W && y < WIN_H && x >= 0 && y >= 0)
		r->win_pixel_buffer[i] = color;
}

/*
**	Initializing bunch of values in separate functions to appease Norminette.
*	Otherwise pixel-accurate line drawing algorithm between 2 point coordinates.
*	Initial checks make sure that drawing works for all angles into
*	every direction. After that, drawline() plots
*	a line of pixels from [point0] to [point1].
*/

static void	init_startingvalues(t_point p0, int *x, int *y)
{
	*x = p0.x;
	*y = p0.y;
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
*	TODO: draw into given buffer instead of pre-chosen render target.
*/
void	draw_line(t_rend *r, t_point p0, t_point p1, uint32_t color)
{
	int		derror;
	int		error;
	int		x;
	int		y;
	t_bool	flip;

	flip = init_points(&p0, &p1);
	init_errors(p0, p1, &derror, &error);
	init_startingvalues(p0, &x, &y);
	while (x <= p1.x && x++)
	{
		if (!flip)
			drawpixel(x - 1, y, r, color);
		else
			drawpixel(y, x - 1, r, color);
		error += derror;
		if (error > p1.x - p0.x)
		{
			if (p1.y > p0.y)
				y += 1;
			else
				y += -1;
			error -= (p1.x - p0.x) * 2;
		}
	}
}

/*
*	Calculates points on the border of the circle in its first octant,
*	rest are determined by symmetry. draw unique points until (x = y)
*	choosing points closest to the radius of the circle.
*/
void	draw_circle(t_rend *rend, t_point p, int r, uint32_t color)
{
	int	x;
	int	y;
	int	d;

	x = r;
	y = 0;
	d = 1 - r;
	while (x >= y)
	{
		drawpixel(p.x + x, p.y + y, rend, color);
		drawpixel(p.x - x, p.y + y, rend, color);
		drawpixel(p.x + x, p.y - y, rend, color);
		drawpixel(p.x - x, p.y - y, rend, color);
		drawpixel(p.x + y, p.y + x, rend, color);
		drawpixel(p.x - y, p.y + x, rend, color);
		drawpixel(p.x + y, p.y - x, rend, color);
		drawpixel(p.x - y, p.y - x, rend, color);
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
void	draw_filled_circle(t_rend *rend, t_point p, int r, uint32_t color)
{
	int	x;
	int	y;
	int	d;

	x = r;
	y = 0;
	d = 1 - r;
	while (x >= y)
	{
		draw_line(rend, (t_point){p.x + x, p.y + y},
			(t_point){p.x - x, p.y + y}, color);
		draw_line(rend, (t_point){p.x + x, p.y - y},
			(t_point){p.x - x, p.y - y}, color);
		draw_line(rend, (t_point){p.x + y, p.y + x},
			(t_point){p.x - y, p.y + x}, color);
		draw_line(rend, (t_point){p.x + y, p.y - x},
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
