#ifndef DOOM_H
# define DOOM_H

# include <unistd.h> //for sleep func
# include <stdint.h>

# include "../libSDL2/include/SDL2/SDL.h"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_gfx.h"

# include "boid.h"
# include "vector.h"

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

//this should probably be generic memory unit for all 'images'
//thats why we probably need offset values. Also BPP might be useless since
//every buffer wants the same 32-bit ARGB values.
//(into which all filedata will be stored inside program memory)
typedef struct s_imgdata {
	uint32_t	*data;
	uint32_t	w;
	uint32_t	h;
	uint32_t	bpp;
	uint32_t	x_pos;
	uint32_t	y_pos;
}				t_imgdata;

//place to hold all graphics etc. data we need. Also development stuff
typedef struct s_assets {
	t_imgdata	*testimg;
	t_boid		flock[BOID_COUNT];
}				t_assets;

t_imgdata	*load_tga(const char *filepath);

//{int x, int y} //Do we want these to be other way around?
typedef struct s_point {
	int	x;
	int	y;
}				t_point;

//testfuncs
void		update_boids(t_boid *flock, t_rend *rend);

void		drawpixel(int x, int y, t_rend *r, uint32_t color);
void		draw_line(t_rend *r, t_point p0, t_point p1, uint32_t color);
void		draw_circle(t_rend *rend, t_point p, int r, uint32_t color);
void		draw_filled_circle(t_rend *rend, t_point p, int r, uint32_t color);
//testfuncs
void		tga_load_test(t_rend *renderer, t_assets *assets);
void		drawlinetest(t_rend *r);

#endif
