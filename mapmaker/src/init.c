#include "mapmaker.h"

/*
** Initialises buttons onto the toolbar.
*/

void	init_buttons(t_img *img)
{
	draw_button(BUTTON_SAVE, img, GREEN);
	draw_button(BUTTON_CNCT, img, RED);
	draw_button(BUTTON_UNDO, img, TEAL);
}

/*
** Initialises the "edit" struct, forms the toolbar, and calls a button drawing
** function.
*/

void	init_editor(t_img *img)
{
	int			i;
	int			j;
	uint32_t	pixel;

	img->edit = ft_calloc(1, sizeof(t_editor));
	if (!img->edit)
		die("Malloc error.");
	j = 0;
	ft_bzero(img->win_buffer->pixels, WIN_MAX * sizeof(uint32_t));
	while (j <= WIN_H)
	{
		i = 0;
		while (i <= TBAR_W)
		{
			pixel = j * WIN_W + i;
			img->win_buffer->pixels[pixel] = BLUE;
			i++;
		}
		j++;
	}
	init_buttons(img);
	img->edit->cnct = TRUE;
	img->edit->redo = FALSE;
	///////// !!!!!!!!!!!
	img->edit->current = NULL;
	img->edit->head = NULL;
	img->edit->tail = NULL;
	img->edit->i = 0;
	img->edit->finished = -1;
	img->edit->clear = FALSE;
}
