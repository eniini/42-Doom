#include "mapmaker.h"

/*
** Handles key events for the mapmaker.
*/

void	key_events(SDL_Event e, t_img *img)
{
	int key;

	key = e.key.keysym.sym;
	if (key == SDLK_ESCAPE)
		img->run = FALSE;
	else if (key == SDLK_c)
		event_clear(img);
	else if (key == SDLK_u)
	//	undo_last(img);
		e_undo_last(img->edit);
	else if (key == SDLK_r && img->edit->redo == TRUE)
		e_redo(img->edit);
	e_draw_map(img, img->edit->head);
	return ;
}
