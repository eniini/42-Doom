#include "doom.h"

/*************************************************************************/
//TODO: blitting to different buffers (that can be of different size than
//program window) means that we should have limits of each buffer saved.
//i.e. buffer being a struct: [start.x > WIN_W -> start.x > buf.width]
/*************************************************************************/

/*
*	Copy [img->data] into [buf] starting the from given x/y coordinates.
*	Returns -1 on error.
*/
int	blit_img(t_imgdata *img, uint32_t *buf, t_point start)
{
	uint32_t	x;
	uint32_t	y;

	if (!img || !buf)
		return (-1);
	if ((start.x > WIN_W || start.x < 0) || (start.y > WIN_H || start.y < 0))
		return (-1);
	y = 0;
	while ((y + start.y) < WIN_H)
	{
		x = 0;
		while ((x + start.x) < WIN_W)
		{
			if (img->data[y * img->w + x] != 0)
			{
				buf[((y + start.y) * WIN_W) + x + start.x] \
				= img->data[y * img->w + x];
			}
			if (x > img->w)
				break ;
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
static void	copy_loop(t_imgdata *o, t_imgdata *n, float step_x, float step_y)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < n->h)
	{
		x = 0;
		while (x < n->w)
		{
			n->data[y * n->w + x] = \
			o->data[((int)floor(y * step_y) * o->w) + (int)floor(x * step_x)];
			x++;
		}
		y++;
	}
}

/*
*	Copies [img->data] into [buf] starting from the given x/y vector using
*	nearest-neighbor technique. [Scale] must be a positive (>=0.1f) scalar.
*	Returns -1 on error.
*/
int	blit_img_scaled(t_imgdata *img, uint32_t *buf, t_point offs, float scale)
{
	t_imgdata	s_img;

	if (!img || !buf || scale < 0.1f)
		return (-1);
	if ((offs.x > WIN_W || offs.x < 0) || (offs.y > WIN_H || offs.y < 0))
		return (-1);
	s_img.w = (uint32_t)(img->w * scale);
	s_img.h = (uint32_t)(img->h * scale);
	s_img.data = ft_memalloc(s_img.w * s_img.h);
	if (!s_img.data)
		return (-1);
	copy_loop(img, &s_img, img->w / (double)s_img.w, img->h / (double)s_img.h);
	if (blit_img(&s_img, buf, offs) < 0)
	{
		free(s_img.data);
		return (-1);
	}
	free(s_img.data);
	return (0);
}
