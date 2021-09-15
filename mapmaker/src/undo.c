#include "mapmaker.h"

/*
** In the case of a undo/redo event, the output of either the
** undo or the working buffer is put out on the output. The
** "redo" flag signifies that a redo action is possible. If a
** disconnected wall piece is undo'd, it is fully erased.
*/

void	undo_last(t_img *img)
{
	t_point	nul;
	int		i;

	i = img->edit->undo->i;
	nul.x = 0;
	nul.y = 0;
	if (img->edit->cnct == FALSE)
	{
		if (img->edit->undo->walls[i].start.x == 0)
		{
			img->edit->undo->i--;
			i = img->edit->undo->i;
			img->edit->undo->walls[i].start = nul;
			img->edit->undo->walls[i].end = nul;
		}
		else
			img->edit->undo->walls[i].start = nul;
		img->edit->undo->finished = -1;
	}
	undo_to_output(img->edit);
	draw_map(img, img->edit->output);
	img->edit->redo = TRUE;
}

void	redo_last(t_img *img)
{
	working_to_output(img->edit);
	draw_map(img, img->edit->output);
	img->edit->redo = FALSE;
}
