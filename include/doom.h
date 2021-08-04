#ifndef DOOM_H
# define DOOM_H

# include <stdint.h>

# include "../libSDL2/include/SDL2/SDL_mixer.h"
# include "../libSDL2/include/SDL2/SDL.h"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_gfx.h"

# define WIN_W 800
# define WIN_H 600
# define WIN_MAX 480000
# define WIN_NAME "DOOM-NUKEM @42 BY ESUKAVA/ENIINI/ESORMUNE"

# define TRUE 1
# define FALSE 0

# define WHITE 0XFFFFFF
# define GREY 0X949494

# include "boid.h"
# include "vector.h"
//# include "resourcefile.h"

# define WIN_W 800
# define WIN_H 600
# define WIN_NAME "DOOM-NUKEM @42 BY ESUKAVA/ENIINI/ESORMUNE"

typedef struct s_point {
	int	x;
	int	y;
}				t_point;

typedef struct s_mouse
{
	t_point	prev;
	t_point	new;
	int		line;
}				t_mouse;

typedef struct s_buffer {
	uint32_t		*pixels;
	uint32_t		w;
	uint32_t		h;
}					t_buffer;

typedef struct s_rend
{
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	uint32_t		*win_pixels;
	t_buffer		win_buffer;
	int				win_pixel_pitch;
	t_bool			run;
	t_mouse			mouse;
}					t_rend;

void	mouse_click(SDL_Event e, t_rend *rend);
void	draw_dot(t_rend *rend, int pixel);
//void	draw_line(t_rend *rend, t_point start, t_point end);

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


int			blit_img(t_imgdata *img, uint32_t *buf, t_point start);
int			blit_img_scaled(t_imgdata *img, uint32_t *buf, \
t_point offs, float scale);

void		drawpixel(uint32_t x, uint32_t y, t_buffer *buffer, uint32_t color);
void		draw_line(t_buffer *buf, t_point p0, t_point p1, uint32_t color);
void		draw_circle(t_buffer *buf, t_point p, int r, uint32_t color);
void		draw_filled_circle(t_buffer *buf, t_point p, int r, uint32_t color);

t_imgdata	*load_tga(const char *filepath);

void		update_boids(t_boid *flock, t_buffer *buf);
void		dotests(t_buffer *buf, t_assets *assets);

#endif