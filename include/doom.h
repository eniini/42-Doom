#ifndef DOOM_H
# define DOOM_H

# include <unistd.h> //for sleep func

# include "../libSDL2/include/SDL2/SDL.h"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_gfx.h"

# define WIN_W 400
# define WIN_H 200
# define WIN_NAME "DOOM-NUKEM @42 BY ESUKAVA/ENIINI/ESORMUNE"

typedef struct s_rend
{
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	uint32_t		*win_pixel_array;
	uint32_t		*win_pixel_buffer;
	int				win_pixel_pitch;
	t_bool			run;
}					t_rend;

#endif
