#include "mapmaker.h"

/*
** Handles the "clear" event. Resets mouse clicked status to non-clicked.
** Erases buffer. Erases saved points of map.
*/

void	clear_canvas(t_img *img)
{
	int			i;
	int			j;
	uint32_t	pixel;

	j = 0;
	while (j <= WIN_H)
	{
		i = TBAR_W;
		while (i <= WIN_W)
		{
			pixel = j * WIN_W + i;
			img->win_buffer->pixels[pixel] = BLACK;
			i++;
		}
		j++;
	}
//	img->edit->finished = -1;
//	clear_buffer(img);
}

/*
** Clears the buffer given to it.
*/

static void	clear_buffer(t_buf *buf)
{
	t_point	nul;
	int		i;

	i = 0;
	nul.x = 0;
	nul.y = 0;
	while (i <= buf->i)
	{
		buf->walls[i].start = nul;
		buf->walls[i].end = nul;
		i++;
	}
	buf->i = 0;
	buf->finished = -1;
}

/*
** Handles clear event by clearing canvas and then the working buffer.
*/

void	event_clear(t_img *img)
{
	working_to_undo(img->edit);
	clear_buffer(img->edit->working);
	working_to_output(img->edit);
	draw_map(img, img->edit->output);
}
