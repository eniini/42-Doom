#include "mapmaker.h"

/*
** Initialises buttons onto the toolbar.
*/
void	e_init_buttons(t_e_img *img)
{
	e_draw_button(BUTTON_SAVE, img, C_GREEN);
	e_draw_button(BUTTON_CNCT, img, C_RED);
	e_draw_button(BUTTON_UNDO, img, C_TEAL);
}

/*
** Initialises the "edit" struct, forms the toolbar, and calls a button drawing
** function.
*/
void	e_init_editor(t_e_img *img)
{
	int			i;
	int			j;
	uint32_t	pixel;

	img->edit = ft_calloc(1, sizeof(t_editor));
	if (!img->edit)
		ft_getout("Malloc error.");
	j = 0;
	ft_bzero(img->win_buffer->px, WIN_H * WIN_W * sizeof(uint32_t));
	while (j < WIN_H)
	{
		i = 0;
		while (i <= TBAR_W)
		{
			pixel = j * WIN_W + i;
			img->win_buffer->px[pixel] = C_BLUE;
			i++;
		}
		j++;
	}
	e_init_buttons(img);
	img->edit->cnct = TRUE;
	img->edit->redo = FALSE;
	img->edit->current = NULL;
	img->edit->head = NULL;
	img->edit->tail = NULL;
	img->edit->clear = FALSE;
}
