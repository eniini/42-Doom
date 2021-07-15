#ifndef DOOM_H
# define DOOM_H

# include <unistd.h> //for sleep func

# include "../libSDL2/include/SDL2/SDL.h"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_gfx.h"

# define WIN_W 800
# define WIN_H 600
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

typedef struct s_imgdata {
	unsigned char	*data;
	uint16_t		w;
	uint16_t		h;
	uint8_t			bpp;
}					t_imgdata;

t_imgdata 	*load_file(const char *filepath);

//testfuncs
void	tga_load_test(t_rend *renderer);

#endif
