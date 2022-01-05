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
*	ui_ = interface
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
# include "render.h"
# include "resourcefile.h"
# include "m_utils.h"

//temp
# define WIN_W 800
# define WIN_H 600
# define WIN_HW 400
# define WIN_HH 300
# define WIN_NAME "DOOM-NUKEM @42 BY ESUKAVA/ENIINI/ESORMUNE"

//COLOURS
# define C_BLUE		0XFF0000FF
# define C_GREEN	0XFF00FF00
# define C_RED		0XFFFF0000
# define C_TEAL		0XFF00FBFF
# define C_GREY		0XFF949494
# define C_BLACK	0xFF000000
# define C_WHITE	0xFFFFFFFF
# define C_GRAY		0xFF808080
# define C_PINK		0xFFE297DF
# define C_PURPLE	0xFF6E26B4
# define C_ORANGE	0xFFE7973D

# define C_DEBUG	0xFF26FF26



typedef	struct	s_tests {

	t_bool		test_active;
	t_bool		test_cube;
	t_bool		test_phys;

}				t_tests;

//Everything audio-related.
//consider changing these in to struct array with enum
typedef struct s_audio {
	Mix_Music	*music;
	Mix_Chunk	*sound;
	Mix_Chunk	*boing;
	Mix_Chunk	*money;
	t_bool		sound_trigger;
	t_bool		boing_trigger;
	t_bool		money_trigger;
	t_bool		music_trigger;
	t_bool		mute_switch;
}				t_audio;

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
	t_font		ui_text_s;
	t_font		ui_text_m;
	t_font		ui_text_ss;
}				t_assets;
//Minimap constitutes an independent rendition of map data and player's position
//in it. Therefore it needs its own set of dynamic units.
typedef struct s_mmap {
	t_vector	max_coord;
	t_vector	min_coord;
	t_vector	coord_diff;
	t_vector	buf_unit;
	t_vector	mm_p_angle;
	t_buffer	*mmapbuf;
	int			scale;
}				t_mmap;
//Holds all the dynamic units related to projecting map geometry into
//screen space.
typedef struct s_map {
	t_vector	max_coord;
	t_vector	min_coord;
	t_vector	coord_diff;
	t_vector	buf_unit;
	t_buffer	*mapbuf;
}				t_map;
//Data related directly to player.
typedef struct s_player {
	t_fvector	pos;
	float		yaw;
	float		yaw_sin;
	float		yaw_cos;
}				t_player;
//Keyevent handling.
typedef struct s_keys {
	t_bool		up_pressed;
	t_bool		down_pressed;
	t_bool		left_pressed;
	t_bool		right_pressed;
	t_bool		fps_switch;
	t_bool		mouse_switch;
	t_bool		rot_switch;
	int			view_switch;
}				t_keys;
//Includes separate framebuffers for static and per-frame generated data.
typedef struct s_ui {
	t_buffer	*db_buf_stat;
	t_buffer	*db_buf_dyn;
	char		ui_str[256];
	t_bool		active;
}				t_ui;
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
	t_vector	mouse;
	t_keys		keys;
	t_ui		ui;
	int			global_fps;
	double		delta;
	t_tests		tests;
	int			cur_sec;
}				t_doom;

int			blit_cropped(t_img *img, t_square s, t_buffer *buf, t_pixel start);
int			blit_img(t_img *img, t_buffer *buf, t_pixel start);
int			blit_img_scaled(t_img *img, t_buffer *buf, t_pixel offs, float s);
t_sprite	*create_sprite(t_img *img, uint32_t count, t_pixel dimensions);
t_bool		blit_sprite(t_sprite *sprite, t_buffer *buf, int i, t_pixel start);

uint32_t	color_lerp(uint32_t c1, uint32_t c2, double p);

void		init_font_atlas(t_font *f, uint fsize, uint atlas_w, uint s_rowc);
t_msg		*create_msg(char *str, uint32_t color, t_pixel pos);
void		delete_msg(t_msg *msg);
void		write_to_buffer(t_buffer *buf, t_font *f, t_msg *msg);

void		init_ui(t_ui *ui);
void		init_debug_elements(t_ui *ui, t_assets *assets);
void		blit_debug_ui(t_doom *doom);

void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		draw_line(t_buffer *buf, t_pixel p0, t_pixel p1, uint32_t color);
//wip
void	draw_line_shaded(t_buffer *buf, t_pixel p0, t_pixel p1, t_pixel c);
//wip
void		draw_circle(t_buffer *buf, t_pixel p, int r, uint32_t color);
void		draw_filled_circle(t_buffer *buf, t_pixel p, int r, uint32_t col);
void		draw_square(t_pixel start, t_pixel end, t_buffer *buf, uint32_t c);
void		draw_vector_line(t_buffer *buf, t_line line, uint32_t c);

void		cull_vertices(t_world *world);
void		draw_visibleverts(t_map *map, t_world *world);
void		init_world(t_world *world, t_map *map, t_buffer *buf);
void		init_minimap(t_world *w, t_mmap *mmmap, t_buffer *buf, uint32_t s);
void		draw_map(t_map *map, t_world *world);
void		draw_minimap(t_mmap *mm, t_world *world);

void		r_dotests(t_doom *doom);
void		draw_cube(t_doom *doom);

void		rotate_player(t_world *world, t_mmap *mmap, int r);

void		apply_perspective(t_world *world);
void		apply_movement(t_world *world, t_vector direction);

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
void		mouse_movement(t_doom *doom);

void	ales_render(t_doom *doom);
#endif
