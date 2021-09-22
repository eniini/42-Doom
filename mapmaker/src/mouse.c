#include "mapmaker.h"

/*
** Toggles the "connect" flag for the editor, then modifies
** the necessary values in order for it to take effect immediately.
*/

static void	toggle_cnct(t_editor *edit)
{
	if (edit->cnct == TRUE)
		edit->cnct = FALSE;
	else
		edit->cnct = TRUE;
}

/*
** Takes in the clicked mouse event and does necessary action based on which button
** has been pressed. Checks where it has been pressed and whether this corresponds to
** a button or to draw on the map.
*/

void	mouse_click(SDL_Event e, t_img *img)
{
	t_point	pixel;

	pixel.x = (uint32_t)e.button.x;
	pixel.y = (uint32_t)e.button.y;
	img->mouse.new = pixel;
	if (e.button.button == 1)
	{
		if (pixel.x >= (TBAR_W + RADIUS))
		{
			if (img->edit->redo == TRUE || img->edit->clear == TRUE)
			{
				e_del_list(&img->edit->tail);
				img->edit->redo = FALSE;
				img->edit->clear = FALSE;
			}
			l_clicked(pixel, img, img->edit);
			e_draw_map(img, img->edit->head);
		}
		else if (pixel.x >= BUTTON_X && pixel.x <= BUTTON_X + BUTTON_SIZE)
		{
//			if (pixel.y >= BUTTON_SAVE && (pixel.y <= BUTTON_SAVE + BUTTON_SIZE))
//				save_map(img);
			if (pixel.y >= BUTTON_CNCT && (pixel.y <= BUTTON_CNCT + BUTTON_SIZE))
				toggle_cnct(img->edit);
			else if (pixel.y >= BUTTON_UNDO && (pixel.y <= BUTTON_UNDO + BUTTON_SIZE))
			{
				e_undo_last(img->edit);
				e_draw_map(img, img->edit->head);
			}
		}
	}
}
