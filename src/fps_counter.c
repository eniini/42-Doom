#include "doom.h"

void	fps_counter(int *global_fps)
{
	static int		i;
	static size_t	sec;
	static size_t	presec;

	sec = SDL_GetTicks();
	if (sec - presec < 1000)
	{
		i++;
	}
	else
	{
		presec = sec;
		*global_fps = i;
		i = 0;
	}
}
