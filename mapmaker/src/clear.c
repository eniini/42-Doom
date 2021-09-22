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
}

void	e_clear(t_editor *edit)
{
	e_del_list(&edit->tail);
	edit->tail = edit->head;
	edit->head = NULL;
	edit->clear = TRUE;
}
