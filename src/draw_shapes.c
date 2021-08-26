/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:01:46 by eniini            #+#    #+#             */
/*   Updated: 2021/08/20 15:33:54 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
		draw_pixel(p.x + x, p.y + y, buf, color);
		draw_pixel(p.x - x, p.y + y, buf, color);
		draw_pixel(p.x + x, p.y - y, buf, color);
		draw_pixel(p.x - x, p.y - y, buf, color);
		draw_pixel(p.x + y, p.y + x, buf, color);
		draw_pixel(p.x - y, p.y + x, buf, color);
		draw_pixel(p.x + y, p.y - x, buf, color);
		draw_pixel(p.x - y, p.y - x, buf, color);
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
*	Avoiding unsigned integer overflow by clamping substractions.
*	Ugly but works.
*/
static void	check_drawline(t_buffer *buf, t_point p, t_point i, uint32_t col)
{
	t_point	diff;
	t_point	crossdiff;

	diff = i;
	if (diff.x > p.x)
		diff.x = p.x;
	if (diff.y > p.y)
		diff.y = p.y;
	crossdiff = i;
	if (crossdiff.x > p.y)
		crossdiff.x = p.y;
	if (crossdiff.y > p.x)
		crossdiff.y = p.x;
	draw_line(buf, (t_point){p.x + i.x, p.y + i.y},
		(t_point){p.x - diff.x, p.y + i.y}, col);
	draw_line(buf, (t_point){p.x + i.x, p.y - diff.y},
		(t_point){p.x - diff.x, p.y - diff.y}, col);
	draw_line(buf, (t_point){p.x + i.y, p.y + i.x},
		(t_point){p.x - crossdiff.y, p.y + i.x}, col);
	draw_line(buf, (t_point){p.x + i.y, p.y - crossdiff.x},
		(t_point){p.x - crossdiff.y, p.y - crossdiff.x}, col);
}

/*
*	Instead of drawing individual pixels on symmetrical positions along the
*	circle's radius, we draw lines from one end to its opposite.
*/
void	draw_filled_circle(t_buffer *buf, t_point p, int r, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;
	int			d;

	x = r;
	y = 0;
	d = 1 - r;
	while (x >= y)
	{
		check_drawline(buf, p, (t_point){x, y}, color);
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
*	Paints a square area of pixels with given color.
*	Ignores calls given with illegal (outside of buffer region) coordinates.
*/
void	draw_square(t_point p0, t_point p1, t_buffer *buf, int color)
{
	uint32_t	x;
	uint32_t	y;

	if ((p0.x > buf->w || p1.x > buf->w) || (p0.y > buf->h || p1.y > buf->h))
		return ;
	if (p1.x < p0.x)
		ft_swap(&p1.x, &p0.x, sizeof(int));
	if (p1.y < p0.y)
		ft_swap(&p1.y, &p0.y, sizeof(int));
	x = p0.x;
	y = p0.y;
	while (y <= p1.y)
	{
		while (x <= p1.x)
		{
			draw_pixel(x, y, buf, color);
			x++;
		}
		x = p0.x;
		y++;
	}
}
