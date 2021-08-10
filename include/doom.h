#ifndef DOOM_H
# define DOOM_H

# include <stdint.h> //for datatypes
# include <string.h> //for sterror
# include <errno.h> //for errno macro

# include "../libSDL2/include/SDL2/SDL_mixer.h"
# include "../libSDL2/include/SDL2/SDL.h"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_gfx.h"

# include "boid.h"
# include "vector.h"
# include "resourcefile.h"

# define WIN_W 800
# define WIN_H 600
# define WIN_NAME "DOOM-NUKEM @42 BY ESUKAVA/ENIINI/ESORMUNE"

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
	void			*win_pixels;
	t_buffer		*win_buffer;
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

//datatype for handling buffer/array coordinates
typedef struct s_point {
	uint32_t	x;
	uint32_t	y;
}				t_point;

int			blit_img(t_imgdata *img, t_buffer *buf, t_point start);
int			blit_img_scaled(t_imgdata *img, t_buffer *buf, \
t_point offs, float scale);

void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		draw_line(t_buffer *buf, t_point p0, t_point p1, uint32_t color);
void		draw_circle(t_buffer *buf, t_point p, int r, uint32_t color);
void		draw_filled_circle(t_buffer *buf, t_point p, int r, uint32_t color);
void		draw_square(t_point a, t_point b, t_buffer *buf, int color);

t_imgdata	*load_tga(const char *filepath);
uint32_t	load_tga_info_rf(const char *filepath, int rf_fd, uint32_t offset);
t_imgdata	*load_tga_from_rf(int fd);

void		update_boids(t_boid *flock, t_buffer *buf);
void		init_tests(t_assets *assets);
void		cleanup_tests(t_assets *assets);
void		dotests(t_buffer *buf, t_assets *assets);

t_imgdata	*load_from_rf(void);

#endif
