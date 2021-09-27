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

# include <string.h> //for sterror
# include <errno.h> //for errno macro

# include "../libSDL2/include/SDL2/SDL_mixer.h"
# include "../libSDL2/include/SDL2/SDL.h"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_gfx.h"

# include "boid.h"
# include "defines.h"
# include "mapdefs.h"
# include "render.h"
# include "resourcefile.h"
# include "vector.h"

# define WIN_W 800
# define WIN_H 600
# define WIN_NAME "DOOM-NUKEM @42 BY ESUKAVA/ENIINI/ESORMUNE"

# define C_BLACK 0x00000000
# define C_WHITE 0x00FFFFFF

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

//sprite in the context of this program refers to struct that 
//holds a spritesheet and from which you can blit individual sprites from.
typedef struct s_sprite {
	t_imgdata	*img;
	uint32_t	sprite_count;
	uint32_t	sprite_w;
	uint32_t	sprite_h;
	uint32_t	width;
}				t_sprite;

//place to hold all graphics etc. data we need. Also development stuff
typedef struct s_assets {
	t_imgdata	*dev_skybox;
}				t_assets;

typedef struct s_audio {
	Mix_Chunk	*sound;
	t_bool		sound_trigger;
}				t_audio;

typedef struct s_mmap {
	t_vert		max_coord;
	t_vert		min_coord;
	t_vert		coord_diff;
	t_vert		buf_unit;
	t_vert		mm_p_angle;
	t_buffer	*mmapbuf;
	int			scale;
}				t_mmap;

typedef struct s_map {
	t_vert		max_coord;
	t_vert		min_coord;
	t_vert		coord_diff;
	t_vert		buf_unit;
	t_buffer	*mapbuf;
}				t_map;

/*
*	Final map structure collection.
*	BSP -> binary tree of convex areas (SUBSECTORS)
*	SEGS -> individual BSP geometry units
*	SECTORS -> collection of properties for a specific area
*	LINEDEFS -> general geometry unit
*	SIDEDEFS -> additional data for LINEDEF texturing
*	VERTICES -> list of all the vertexes in the map
*/
typedef struct s_mapdata
{
	t_me_node	*bsp;
	t_l_segs	*r_segs;
	t_l_sectors	*lv_sectors;
	t_l_ldefs	*lv_linedefs;
	t_l_sdefs	*lv_sidedefs;
	t_l_things	*lv_things;
	short		vertices[SHRT_MAX][2];
}				t_mapdata;

typedef struct s_player {
	t_f_point		pos;
}				t_player;

typedef struct s_keys {
	t_bool	up_pressed;
	t_bool	down_pressed;
	t_bool	left_pressed;
	t_bool	right_pressed;
}				t_keys;

//superstruct that holds all the subsystem structs
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
	t_mapdata	mapdata;
}				t_doom;

int			blit_img(t_imgdata *img, t_buffer *buf, t_point start);
int			blit_img_scaled(t_imgdata *img, t_buffer *buf, \
t_point offs, float scale);

t_sprite	*create_sprite(t_imgdata *img, uint32_t spr_count, \
t_point spr_unit);
t_bool		blit_sprite(t_sprite *sprite, t_buffer *buf, int i, t_point pos);

void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		draw_line(t_buffer *buf, t_point p0, t_point p1, uint32_t color);
void		draw_circle(t_buffer *buf, t_point p, int r, uint32_t color);
void		draw_filled_circle(t_buffer *buf, t_point p, int r, uint32_t color);
void		draw_square(t_point a, t_point b, t_buffer *buf, int color);

void		cull_vertices(t_world *world);
void		draw_visibleverts(t_map *map, t_world *world);
void		init_world(t_world *world, t_map *map, t_buffer *buf);
void		init_minimap(t_world *w, t_mmap *mmmap, t_buffer *buf, uint32_t s);
void		draw_map(t_map *map, t_world *world);
void		draw_minimap(t_mmap *mm, t_world *world);

void		r_dotests(t_rend *rend, t_world *w);

void		rotate_player(t_world *world, t_mmap *mmap, int r);

void		apply_perspective(t_world *world);
void		apply_movement(t_world *world, t_vert direction);

t_imgdata	*load_tga(const char *filepath);
void		add_tga_to_rf(t_rf *rf, const char *filepath);
t_imgdata	*load_tga_from_rf(t_rf *rf, short lump_id);
t_imgdata	*rf_load_tga_lump(t_rf *rf, short lump_id);

void		update_boids(t_boid *flock, t_buffer *buf);
void		init_tests(t_doom *doom);
void		dotests(t_doom *doom);
void		cleanup_tests(t_assets *assets);

void		init_audio(t_audio *audio);
void		audio_cleanup(t_audio *audio);
void		audios(t_audio *audio);

void		physics(t_doom *doom);
void		keyevent(t_doom *doom, SDL_Event *e);
void		fps_counter(int *global_fps);
#endif
