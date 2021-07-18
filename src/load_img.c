#include "doom.h"

/*
void	blit_img(t_imgdata *img, int xpos, int ypos, uint32_t *buf)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			buf[y * WIN_W + x + xpos] = img->data[y * img->w + x];
		}
	}
}*/


/*
*	TODO: suite of functions to "blit" imgdata structs in a buffer cleanly
*	handling offsets, scaling etc. Probably could add VFX as well.
*/
void	tga_load_test(t_rend *renderer)
{
	t_imgdata	*testimg;
	uint32_t	i;
	uint32_t	j;

	testimg = load_tga("resources/FEalm.tga");
	if (!testimg)
		ft_getout("failed to load tga!");
	i = 0;
	while (i < testimg->h)
	{
		j = 0;
		while (j < testimg->w)
		{
			renderer->win_pixel_buffer[i * WIN_W + j] = \
			testimg->data[i * testimg->w + j];
			j++;
		}
		i++;
	}
}
