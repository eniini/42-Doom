#include "doom.h"


static void	rotate_room(t_room *room, int p_angle, int p_rotation)
{
	int		i;
	double	c;
	double	s;
	int		angle;

	i = 0;
	angle = (p_angle + p_rotation) % 360;
	c = cos(angle * DEG_TO_RAD);
	s = sin(angle * DEG_TO_RAD);
	while (i < room->wallcount)
	{
		room->proj_walls[i].start.x = (int)round(room->walls[i].start.x * c - room->walls[i].start.y * s);
		room->proj_walls[i].start.y = (int)round(room->walls[i].start.x * s + room->walls[i].start.y * c);
		room->proj_walls[i].end.x = (int)round(room->walls[i].end.x * c + room->walls[i].end.y * s);
		room->proj_walls[i].end.y = (int)round(room->walls[i].end.x * -s + room->walls[i].end.y * c);
		//ft_printf("start:[%d|%d]\tend[%d|%d]\n", room->proj_walls[i].start.x, room->proj_walls[i].start.y, room->proj_walls[i].end.x, room->proj_walls[i].end.y);
		//ft_printf("angle:[%d]\n", angle);
		i++;
	}
}

static void projection_events(t_doom *doom, SDL_Event *e)
{
	if (e->window.event == SDL_WINDOWEVENT_CLOSE)
		doom->rend.run = FALSE;
	if (e->key.keysym.sym == SDLK_q && doom->world.cam_fov > 1)
	{
		doom->world.cam_fov--;
		doom->world.m_proj = mm_init_3d_projection(doom->world.cam_fov, \
		(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
	}
	if (e->key.keysym.sym == SDLK_e && doom->world.cam_fov < 180)
	{
		doom->world.cam_fov++;
		doom->world.m_proj = mm_init_3d_projection(doom->world.cam_fov, \
		(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
	}
	if (e->key.keysym.sym == SDLK_UP)
		doom->world.cam_distance += 0.1f;
	if (e->key.keysym.sym == SDLK_DOWN && doom->world.cam_distance > 1.0f)
		doom->world.cam_distance -= 0.1f;
}

void	keyevent(t_doom *doom, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		projection_events(doom, e);
		if (e->window.event == SDL_WINDOWEVENT_CLOSE)
			doom->rend.run = FALSE;
		if (e->key.keysym.sym == SDLK_UP)
			doom->keys.up_pressed = e->type == SDL_KEYDOWN;
		if (e->key.keysym.sym == SDLK_DOWN)
			doom->keys.down_pressed = e->type == SDL_KEYDOWN;
		if (e->key.keysym.sym == SDLK_LEFT)
			doom->keys.left_pressed = e->type == SDL_KEYDOWN;
		if (e->key.keysym.sym == SDLK_RIGHT)
			doom->keys.right_pressed = e->type == SDL_KEYDOWN;
		if (e->key.keysym.sym == SDLK_r) //testing map/player rotation
		{
			 doom->world.player_rotation++;
			 rotate_room(doom->world.room, doom->world.player_angle, doom->world.player_rotation);
			//rotate_player(&doom->world, &doom->mmap, 1);
			//cull_vertices(&doom->world);
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_m) //mouse_swich
		{
			ft_printf("CLICK\n");
			if (doom->mouse_switch == FALSE)
				doom->mouse_switch = TRUE;
			else
				doom->mouse_switch = FALSE;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_t) //fps_swich
		{
			ft_printf("CLICK\n");
			if(doom->fps_switch == FALSE)
				doom->fps_switch = TRUE;
			else
				doom->fps_switch = FALSE;
		}
	}
}