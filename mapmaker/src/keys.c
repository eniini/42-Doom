#include "mapmaker.h"

/*
** Handles key events for the mapmaker.
*/
void	e_keys(SDL_Event e, t_e_img *img)
{
	int key;

	key = e.key.keysym.sym;
	if (key == SDLK_ESCAPE)
		img->run = FALSE;
	else if (key == SDLK_c)
		e_clear(img, img->edit);
	else if (key == SDLK_u)
		e_undo(img, img->edit);
	else if (key == SDLK_r && img->edit->redo == TRUE)
		e_redo(img->edit);
	e_draw_map(img, img->edit->head);
}
