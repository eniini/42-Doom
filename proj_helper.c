//COMPILE WITH
//gcc proj_testing.c proj_helper.c -Wall -Wextra -Werror `libSDL2/bin/sdl2-config --cflags --libs` -L./libft/ -lft -lm -o projection

#include "libft/includes/libft.h"
#include "stdint.h"

typedef struct s_pixel {
	uint32_t	x;
	uint32_t	y;
}				t_pixel;

typedef struct s_img {
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_img;
typedef t_img	t_buffer;

typedef struct s_vector {
	int	x;
	int	y;
	int	z;
}		t_vector;

typedef struct s_line {
	t_vector	start;
	t_vector	end;
	uint32_t	color;
}				t_line;

static void	draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color)
{
	uint32_t	i;

	i = (buf->w * y) + x;
	if (x < buf->w && y < buf->h)
		buf->px[i] = color;
}

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
		rv.y = v0.y + (v1.y - v0.y) * -v0.x / (v1.x - v0.x);
		rv.x = 0;
	}
	return (rv);
}

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

void	drawtriangle(t_buffer *buf, t_vector v1, t_vector v2, t_vector v3)
{
	draw_vector_line(buf, (t_line){v1, v2, 0}, 0xffa6a6a6);
	draw_vector_line(buf, (t_line){v2, v3, 0}, 0xff848484);
	draw_vector_line(buf, (t_line){v3, v1, 0}, 0xff4f4f4f);
}