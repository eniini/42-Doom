#include "mapmaker.h"


/*
** Draws points for the map. If not the first clicked point,
** draws a connecting line. Saves the pixel point into the vertex buffer.
** Increments buffer counter.
*/

// TODO maybe better to make a sep function for it line vs no line, or button to
// hold if no line?

void	set_walls(t_point pixel, t_img *img, t_buf *buf)
{
//	printf("i is %d, finished is %d\n", buf->i, buf->finished);
	if (buf->i < W_BUFF_SIZE && (buf->finished == -1
		|| (img->mouse.new.x != img->mouse.prev.x
		|| img->mouse.new.y != img->mouse.prev.y)))
	{
		img->mouse.prev = pixel;
		if (buf->finished == -1)
		{
			buf->walls[buf->i].start = pixel;
			buf->finished = FALSE;
		}
		else if (buf->finished == FALSE)
		{
			buf->walls[buf->i].end = pixel;
			buf->finished = TRUE;
		}
		if (buf->finished == TRUE)
		{
			buf->i++;
			buf->finished = -1;
			if (img->edit->cnct == TRUE)
			{
				buf->walls[buf->i].start = pixel;
				buf->finished = FALSE;
			}
		}		
	}
}
