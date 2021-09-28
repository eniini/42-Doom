#ifndef DOOM_H
# define DOOM_H

/*
*	File/datatype terminology:
*	hu_ = HUD
*	m_  = menu
*	me_ = map editor
*	l_  = linked list
*	lv_ = level
*	r_  = renderer
*	rf_ = resource file
*	p_  = gameplay
*	s_  = sound
*/

//c lib
# include <string.h> //for sterror
# include <errno.h> //for errno macro
# include <unistd.h> //for write TBD
//SDL
# include "../libSDL2/include/SDL2/SDL_mixer.h"
# include "../libSDL2/include/SDL2/SDL.h"
//libft
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_gfx.h"
//doom
# include "defines.h"
# include "mapdefs.h"
# include "render.h"
# include "resourcefile.h"
# include "vector.h"

//temp
# define WIN_W 800
# define WIN_H 600
# define WIN_NAME "DOOM-NUKEM @42 BY ESUKAVA/ENIINI/ESORMUNE"

//COLOURS
# define C_BLUE		0XFF0000FF
# define C_GREEN	0XFF00FF00
# define C_RED		0XFFFF0000
# define C_TEAL		0XFF00FBFF
# define C_GREY		0XFF949494
# define C_BLACK	0xFF000000
# define C_WHITE	0xFFFFFFFF

//Holds everything related directly to SDL's drawbuffer.
typedef struct s_rend
{
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	void			*win_pixels;
	t_buffer		*win_buffer;
	int				win_pixel_pitch;
	t_bool			run;
}					t_rend;
//Sprite in the context of this program refers to struct that 
//holds a spritesheet and from which you can blit individual sprites from.
typedef struct s_sprite {
	t_img		*img;
	uint32_t	sprite_count;
	uint32_t	sprite_w;
	uint32_t	sprite_h;
	uint32_t	width;
}				t_sprite;
//Place to hold all graphics etc. data we need. Also development stuff
typedef struct s_assets {
	t_img		*dev_skybox;
}				t_assets;
//Everything audio-related.
typedef struct s_audio {
	Mix_Chunk	*sound;
	t_bool		sound_trigger;
}				t_audio;
//Minimap constitutes an independent rendition of map data and player's position
//in it. Therefore it needs its own set of dynamic units.
typedef struct s_mmap {
	t_point2	max_coord;
	t_point2	min_coord;
	t_point2	coord_diff;
	t_point2	buf_unit;
	t_point2	mm_p_angle;
	t_buffer	*mmapbuf;
	int			scale;
}				t_mmap;
//Holds all the dynamic units related to projecting map geometry into
//screen space.
typedef struct s_map {
	t_point2	max_coord;
	t_point2	min_coord;
	t_point2	coord_diff;
	t_point2	buf_unit;
	t_buffer	*mapbuf;
}				t_map;
//Data related directly to player.
typedef struct s_player {
	t_vector2	pos;
}				t_player;
//Keyevent handling.
typedef struct s_keys {
	t_bool		up_pressed;
	t_bool		down_pressed;
	t_bool		left_pressed;
	t_bool		right_pressed;
}				t_keys;
//superstruct that holds all the subsystem structs.
typedef struct s_doom {
	t_rend		rend;
	t_assets	assets;
	t_rf		rf;
	t_audio		audio;
	t_world		world;
	t_map		map;
	t_mmap		mmap;
	t_player	player;
	t_keys		keys;
	int			global_fps;
	double		delta;
	t_bool		fps_switch;
	t_dbg_room	*room;
}				t_doom;


int			blit_img(t_img *img, t_buffer *buf, t_point2 start);
int			blit_img_scaled(t_img *img, t_buffer *buf, t_point2 offs, float s);
t_sprite	*create_sprite(t_img *img, uint32_t count, t_point2 dimensions);
t_bool		blit_sprite(t_sprite *sprite, t_buffer *buf, int i, t_point2 start);

void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		draw_line(t_buffer *buf, t_point2 p0, t_point2 p1, uint32_t color);
void		draw_circle(t_buffer *buf, t_point2 p, int r, uint32_t color);
void		draw_filled_circle(t_buffer *buf, t_point2 p, int r, uint32_t col);
void		draw_square(t_point2 a, t_point2 b, t_buffer *buf, int color);

void		cull_vertices(t_world *world);
void		draw_visibleverts(t_map *map, t_world *world);
void		init_world(t_world *world, t_map *map, t_buffer *buf);
void		init_minimap(t_world *w, t_mmap *mmmap, t_buffer *buf, uint32_t s);
void		draw_map(t_map *map, t_world *world);
void		draw_minimap(t_mmap *mm, t_world *world);

void		r_dotests(t_rend *rend, t_dbg_room *room);

void		rotate_player(t_world *world, t_mmap *mmap, int r);

void		apply_perspective(t_world *world);
void		apply_movement(t_world *world, t_point2 direction);

t_img		*load_tga(const char *filepath);
void		add_tga_to_rf(t_rf *rf, const char *filepath);
t_img		*load_tga_from_rf(t_rf *rf, short lump_id);
t_img		*rf_load_tga_lump(t_rf *rf, short lump_id);

void		init_tests(t_doom *doom);
void		dotests(t_doom *doom);
void		cleanup_tests(t_doom *doom);

void		init_audio(t_audio *audio);
void		audio_cleanup(t_audio *audio);
void		audios(t_audio *audio);

void		physics(t_doom *doom);
void		keyevent(t_doom *doom, SDL_Event *e);
void		fps_counter(int *global_fps);
#endif
