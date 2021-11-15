#include "doom.h"

/*
*	Copies the data inside [crop] from [img] into [buf], which is
*	offset by [start].
*/
int	blit_cropped(t_img *img, t_square s, t_buffer *buf, t_pixel start)
{
	uint32_t	x;
	uint32_t	y;

	if (!img || !buf)
		return (-1);
	if (start.x > buf->w || start.y > buf->h)
		return (-1);
	y = 0;
	while ((y + start.y) < buf->h && (y + s.start.y) < s.end.y)
	{
		x = 0;
		while ((x + start.x) < buf->w && (x + s.start.x) < s.end.x)
		{
			if (img->px[y * img->w + (x + s.start.x)] != 0)
			{
				buf->px[((y + start.y) * buf->w) + x + start.x] \
				= img->px[img->w * (y + s.start.y) + (s.start.x + x)];
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
*	Copy [img->px] into [buf->px] starting the from given x/y coordinates.
*	Returns -1 on error.
*/
int	blit_img(t_img *img, t_buffer *buf, t_pixel start)
{
	uint32_t	x;
	uint32_t	y;

	if (!img || !buf)
		return (-1);
	if (start.x > buf->w || start.y > buf->h)
		return (-1);
	y = 0;
	while ((y + start.y) < buf->h && y < img->h)
	{
		x = 0;
		while ((x + start.x) < buf->w && x < img->w)
		{
			if (img->px[y * img->w + x] != 0)
			{
				buf->px[((y + start.y) * buf->w) + x + start.x] \
				= img->px[y * img->w + x];
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
*	Subfunction for blit_img_scaled(). Handles copying pixels from one buffer
*	to the other.
*/
static void	copy_loop(t_img *old, t_img *new, float step_x, float step_y)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < new->h)
	{
		x = 0;
		while (x < new->w)
		{
			new->px[y * new->w + x] = \
			old->px[((int)floor(y * step_y) * old->w) + (int)floor(x * step_x)];
			x++;
		}
		y++;
	}
}

/*
*	Copies [img->data] into [buf] starting from the given x/y vector using
*	nearest-neighbor technique. [s] must be a positive (>=0.1f) scalar.
*	Returns -1 on error.
*/
int	blit_img_scaled(t_img *img, t_buffer *buf, t_pixel offs, float s)
{
	t_img	s_img;

	if (!img || !buf || s < 0.1f)
		return (-1);
	if (offs.x > buf->w || offs.y > buf->h)
		return (-1);
	s_img.w = (uint32_t)(img->w * s);
	s_img.h = (uint32_t)(img->h * s);
	s_img.px = ft_memalloc(s_img.w * s_img.h);
	if (!s_img.px)
		return (-1);
	copy_loop(img, &s_img, img->w / (double)s_img.w, img->h / (double)s_img.h);
	if (blit_img(&s_img, buf, offs) < 0)
	{
		free(s_img.px);
		return (-1);
	}
	free(s_img.px);
	return (0);
}
