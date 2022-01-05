/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:54:01 by eniini            #+#    #+#             */
/*   Updated: 2021/12/08 20:35:20 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
*	Initializing bunch of values in separate functions to appease Norminette.
*	Otherwise pixel-accurate line drawing algorithm between 2 point coordinates.
*
*	Initial checks swap point data if needed since drawfunc always traverses
*	from left to right. [flip] checks if we're incrementing through x or y.
*	After that, drawline() plots a line of pixels from [p0] to [p1].
*/

static void	init_errors(t_pixel p0, t_pixel p1, int *derror, int *error)
{
	uint32_t	ydiff;

	if (p1.y > p0.y)
		ydiff = p1.y - p0.y;
	else
		ydiff = p0.y - p1.y;
	*derror = ydiff * 2;
	*error = 0;
}

static t_bool	init_points(t_pixel *p0, t_pixel *p1)
{
	t_bool		flip;
	uint32_t	xdiff;
	uint32_t	ydiff;

	flip = FALSE;
	if (p0->x > p1->x)
		xdiff = p0->x - p1->x;
	else
		xdiff = p1->x - p0->x;
	if (p0->y > p1->y)
		ydiff = p0->y - p1->y;
	else
		ydiff = p1->y - p0->y;
	if (xdiff < ydiff)
	{
		ft_swap(&p0->x, &p0->y, sizeof(uint32_t));
		ft_swap(&p1->x, &p1->y, sizeof(uint32_t));
		flip = TRUE;
	}
	if (p0->x > p1->x)
	{
		ft_swap(&p0->x, &p1->x, sizeof(uint32_t));
		ft_swap(&p0->y, &p1->y, sizeof(uint32_t));
	}
	return (flip);
}

/*
*	Values larger than given buffer dimensions are clamped 
*	to avoid integer overflow related problems.
*	Crawling from screenspace to UINT_MAX practically kills the program.
*/
static void	clamp_values(t_buffer *buf, t_pixel *p0, t_pixel *p1)
{
	if (p0->x > buf->w)
		p0->x = buf->w;
	if (p0->y > buf->h)
		p0->y = buf->h;
	if (p1->x > buf->w)
		p1->x = buf->w;
	if (p1->y > buf->h)
		p1->y = buf->h;
}

/*
*	Bresenham's line algorithm. Plots a line from [p0] to [p1].
*/
void	draw_line(t_buffer *buf, t_pixel p0, t_pixel p1, uint32_t color)
{
	int			derror;
	int			error;
	t_pixel		crawler;
	t_bool		flip;

	clamp_values(buf, &p0, &p1);
	flip = init_points(&p0, &p1);
	crawler = (t_pixel){p0.x, p0.y};
	init_errors(p0, p1, &derror, &error);
	while (crawler.x <= p1.x)
	{
		if (!flip)
			draw_pixel(crawler.x++, crawler.y, buf, color);
		else
			draw_pixel(crawler.y, crawler.x++, buf, color);
		error += derror;
		if (error > (int)p1.x - (int)p0.x)
		{
			if (p1.y > p0.y)
				crawler.y += 1;
			else
				crawler.y += -1;
			error -= ((int)p1.x - (int)p0.x) * 2;
		}
	}
}

/*
*	Because of how dumb this version of drawline is atm, third pixel consists
*	of start/end uint values! x=start y=end.
*/
void	draw_line_shaded(t_buffer *buf, t_pixel p0, t_pixel p1, t_pixel c)
{
	int			derror;
	int			error;
	t_pixel		crawler;
	t_bool		flip;
	uint32_t	col;

	clamp_values(buf, &p0, &p1);
	flip = init_points(&p0, &p1);
	crawler = (t_pixel){p0.x, p0.y};
	init_errors(p0, p1, &derror, &error);
	while (crawler.x <= p1.x)
	{
		if (!flip)
		{
			col = color_lerp(c.x, c.y, crawler.x / (float)p1.x);
			draw_pixel(crawler.x++, crawler.y, buf, col);
		}
		else
		{
			col = color_lerp(c.y, c.x, crawler.x / (float)p1.x);
			draw_pixel(crawler.y, crawler.x++, buf, col);
		}
		error += derror;
		if (error > (int)p1.x - (int)p0.x)
		{
			if (p1.y > p0.y)
				crawler.y += 1;
			else
				crawler.y += -1;
			error -= ((int)p1.x - (int)p0.x) * 2;
		}
	}
}
