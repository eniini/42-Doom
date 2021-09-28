#include "mapmaker.h"

/*
** Draws a square button.
*/
void	e_draw_button(int y_start, t_e_img *img, uint32_t colour)
{
	int	x;
	int	x_end;
	int	y_end;
	int	pixel;

	x = BUTTON_X;
	x_end = x + BUTTON_SIZE;
	y_end = y_start + BUTTON_SIZE;
	while (y_start <= y_end)
	{
		x = BUTTON_X;
		while (x <= x_end)
		{
			pixel = y_start * WIN_W + x;
			img->win_buffer->px[pixel] = colour;
			x++;
		}
		y_start++;
	}
}
