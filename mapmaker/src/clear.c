#include "mapmaker.h"

/*
** Clears all the data that has been stored in the tail's
** storage, then sets the entirety of the head as the new
** tail, so we can return to it. Sets head at NULL to clear it.
** Clears previous mouse point to make sure the clicked
** point spawns. Sets the current pointer to the head.
*/

void	e_clear(t_e_img *img, t_editor *edit)
{
	img->mouse.prev.x = 0;
	img->mouse.prev.y = 0;
	if (!edit->head)
		return ;
	if (edit->tail)
		w_del_list(&edit->tail);
	edit->tail = edit->head;
	edit->head = NULL;
	edit->current = edit->head;
	edit->clear = TRUE;
	edit->redo = FALSE;
}
