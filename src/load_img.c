#include "doom.h"

void	tga_load_test(t_rend *renderer)
{
	t_imgdata	*testimg;
	int i = 0, j = 0;

	testimg = load_file("resources/FEalm.tga");
	if (!testimg)
		ft_getout("failed to load tga!");
	i = 0;
	while (i < testimg->h) //need standard function out of this, including x/y offsets
	{
		j = 0;
		while (j < testimg->w)
		{
			renderer->win_pixel_buffer[i * WIN_W + j] = testimg->imgdata[i * testimg->w + j];
			j++;
		}
		i++;
	}
}
