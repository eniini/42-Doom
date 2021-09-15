#include "mapmaker.h"


/*
** Draws the map. First clears canvas, then goes until the integer limit
** is reached or an empty spot is found; draws a circle onto the point in
** every case, and if an end point is specified, draws a connecting line.
*/

void	draw_map(t_img *img, t_buf *output)
{
	int	i;

	i = 0;
	clear_canvas(img);
//	printf("output i %d, walls i %d\n", output->i, output->walls[i].start.x);
	while (i <= output->i && output->walls[i].start.x != 0)
	{
		if (output->walls[i].end.x != 0)
		{
			draw_line(img->win_buffer, output->walls[i].start,
				output->walls[i].end, GREY);
			draw_filled_circle(img->win_buffer, output->walls[i].end, RADIUS, WHITE);
		}
		draw_filled_circle(img->win_buffer, output->walls[i].start, RADIUS, WHITE);
		i++;
	}
}
