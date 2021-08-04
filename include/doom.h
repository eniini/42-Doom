#ifndef DOOM_H
# define DOOM_H

# include <unistd.h> //for sleep func

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

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_mouse
{
	t_point	prev;
	t_point	new;
	int		line;
}				t_mouse;

typedef struct s_rend
{
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	uint32_t		*win_pixel_array;
	uint32_t		*win_pixel_buffer;
	int				win_pixel_pitch;
	t_bool			run;
	t_mouse			mouse;
}					t_rend;

void	mouse_click(SDL_Event e, t_rend *rend);
void	draw_dot(t_rend *rend, int pixel);
void	draw_line(t_rend *rend, t_point start, t_point end);

#endif
