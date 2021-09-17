#include "mapmaker.h"

/*
** Toggles the "connect" flag for the editor, then modifies
** the necessary values in order for it to take effect immediately.
*/

static void	toggle_cnct(t_editor *edit)
{
	t_point	nul;
	int		i;

	nul.x = 0;
	nul.y = 0;
	i = edit->working->i;
	if (edit->cnct == TRUE)
	{
		edit->cnct = FALSE;
		edit->working->walls[i].start = nul;
		edit->working->finished = -1;
	}
	else
	{
		edit->cnct = TRUE;
		edit->working->walls[i].start = edit->working->walls[i - 1].end;
		edit->working->finished = FALSE;
	}
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
/*			if (img->edit->redo == FALSE)
			{
				working_to_undo(img->edit);
				set_walls(pixel, img, img->edit->working);
				working_to_output(img->edit);
				draw_emap(img, img->edit->output);
			}
			else
			{
				undo_to_working(img->edit);
				set_walls(pixel, img, img->edit->working);
				working_to_output(img->edit);
				draw_emap(img, img->edit->output);
				img->edit->redo = FALSE;
			}*/
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
				undo_last(img);
		}
	}
}
