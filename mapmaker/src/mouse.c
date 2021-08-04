#include "doom.h"
#include <stdio.h>

/*
** Takes in the clicked mouse event and does necessary action based on which button
** has been pressed.
*/

void	mouse_click(SDL_Event e, t_rend *rend)
{
	int	x;
	int	y;
	int	pixel;

	x = e.button.x;
	y = e.button.y;
	rend->mouse.new.x = x;
	rend->mouse.new.y = y;
	pixel = y * WIN_W + x;
	if (e.button.button == 1)
	{
		if (rend->mouse.line == -1 || (rend->mouse.new.x != rend->mouse.prev.x \
			&& rend->mouse.new.y != rend->mouse.prev.y))
		{
			if (rend->mouse.line == TRUE)
			{
				draw_line(rend, rend->mouse.prev, rend->mouse.new);
				rend->mouse.prev.x = rend->mouse.new.x;
				rend->mouse.prev.y = rend->mouse.new.y;
			}
			if (rend->mouse.line == -1)
			{
				rend->mouse.prev.x = x;
				rend->mouse.prev.y = y;
				rend->mouse.line = TRUE;
			}
			draw_dot(rend, pixel);
		}
	}
}
