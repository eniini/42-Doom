#include "doom.h"

void	tga_load_test(t_rend *renderer)
{
	t_imgdata	*testimg;
	int i = 0, j = 0;
	//uint32_t	color;
	uint32_t	*img;

	testimg = load_file("resources/FEalm.tga");
	if (!testimg)
		ft_getout("failed to load tga!");
	img = malloc(sizeof(uint32_t) * testimg->h * testimg->w);
	if (!img)
		ft_getout("malloc failure");
	while (i < WIN_H)
	{
		int k = 0;
		j = 0;
		while (j < testimg->w)
		{
			/*
			//color = ((testimg->data[(i * testimg->w) + j]) | \
				(testimg->data[(i * testimg->w) + j + 1] << 8) | \
				(testimg->data[(i * testimg->w) + j + 2] << 16) | \
				(testimg->data[(i * testimg->w) + j + 3] << 24));
			renderer.win_pixel_buffer[i * WIN_W + j] = color;*/
			//img[(i * testimg->w) + j] = color;
			img[(i * testimg->w) + j] = (testimg->data[(i * testimg->w) + k]);
			img[(i * testimg->w) + j] += (testimg->data[(i * testimg->w) + k + 1]) << 8;
			img[(i * testimg->w) + j] += (testimg->data[(i * testimg->w) + k + 2]) << 16;
			img[(i * testimg->w) + j] += (testimg->data[(i * testimg->w) + k + 3]) << 24;
			j++;
			k += 4;
		}
		i++;
	}
	i = 0;
	while (i < WIN_H && i < testimg->h) //need standard function out of this, including x/y offsets
	{
		j = 0;
		while (j < WIN_W && j < testimg->w)
		{
			renderer->win_pixel_buffer[i * WIN_W + j] = img[i * testimg->w + j];
			j++;
		}
		i++;
	}
}
