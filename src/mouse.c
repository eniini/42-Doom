#include "doom.h"

void	mouse_movement(t_doom *doom)
{
		int x, y;

		if(doom->keys.mouse_switch == TRUE)
		{
			SDL_GetMouseState(&x, &y);
			doom->mouse.x = x;
			doom->mouse.y = y;
			SDL_WarpMouseInWindow(doom->rend.win, WIN_W / 2, WIN_H /2);
			SDL_ShowCursor( SDL_DISABLE );
	//		printf("m_x = %d\tm_y = %d\n", doom->mouse.x, doom->mouse.y);
		}
		else
			SDL_ShowCursor(SDL_ENABLE);
}