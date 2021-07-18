#include "doom.h"

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
*	TODO: suite of functions to "blit" imgdata structs in a buffer cleanly
*	handling offsets, scaling etc. Probably could add VFX as well.
*/
void	tga_load_test(t_rend *renderer, t_assets *assets)
{	
	static uint32_t	x;
	static uint32_t	y;

	if (blit_img(assets->testimg, renderer->win_pixel_buffer, \
		(t_point){x, y}) < 0)
		ft_getout("blit out of bounds / Nulpointer");
	if (y < WIN_H)
	{
		if (x < WIN_W)
			x++;
		else
		{
			x = 0;
			y += WIN_H / 10;
		}
	}
	else
		y = 0;
}
