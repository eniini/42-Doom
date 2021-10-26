#include "doom.h"

float	DotProduct(t_fvector v1, t_fvector v2)
{
	return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

//**
//This accelerate function is from quake source code.
//**
void	accelerate (t_fvector *velocity, float wishspeed, float sv_accelerate, t_fvector *wishdir, t_doom *doom)
{
	float		addspeed, accelspeed, currentspeed;

	currentspeed = DotProduct (*velocity, *wishdir);
	addspeed = wishspeed - currentspeed;
	if (addspeed <= 0)
		return;
	accelspeed = sv_accelerate*doom->delta*wishspeed;
	if (accelspeed > addspeed)
		accelspeed = addspeed;
	
	velocity->x += accelspeed * wishdir->x;	
	velocity->y += accelspeed * wishdir->y;	
	velocity->z += accelspeed * wishdir->z;	
}

void	dir_arrow(t_doom *doom)
{
	static t_vector	result;
	static t_vector	orbiter;
	static t_pixel	pixel;
	
	orbiter.x = doom->player.pos.x + 40;
	orbiter.y = doom->player.pos.y;
	result = vector2_rotate(orbiter, (t_vector){doom->player.pos.x, doom->player.pos.y, 0}, doom->player.yaw);
	if (result.x < 0) //we need a func for this stuff!
		pixel.x = 0;
	else
		pixel.x = result.x;
	if (result.y < 0)
		pixel.y = 0;
	else
		pixel.y = result.y;	
	draw_line(doom->rend.win_buffer, (t_pixel){doom->player.pos.x, doom->player.pos.y}, pixel, 0xFFFFFFFF);
}

// sv_accelerate is constant
void	physics(t_doom *doom)
{
	static int		ticks;
	static int		prevtics;
	static t_fvector		velocity;
	float			wishspeed = 50;
	t_fvector		dir = (t_fvector){0, 0, 0};
	float sv_accelerate = 5;
	prevtics = ticks;
	ticks = SDL_GetTicks();
	doom->delta = (ticks - prevtics) / 1000.0;
	
	doom->player.yaw = doom->player.yaw + (doom->mouse.x - WIN_W / 2);
//	doom->player.yaw_sin = sin(doom->player.yaw);
//	doom->player.yaw_cos = cos(doom->player.yaw);
	if (doom->keys.up_pressed == TRUE)
	{	
		dir.x = (dir.x + cos(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
		dir.y = (dir.y + sin(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
	}
	if (doom->keys.down_pressed == TRUE)
	{
		dir.x = (dir.x - cos(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
		dir.y = (dir.y - sin(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
	}
	if (doom->keys.left_pressed == TRUE)	
	{
		dir.x = (dir.x + sin(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
		dir.y = (dir.y - cos(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
	}
	if (doom->keys.right_pressed == TRUE)
	{
		dir.x = (dir.x - sin(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
		dir.y = (dir.y + cos(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
	}
//	wishspeed = sqrt(dir.x * dir.x + dir.y * dir.y);
	accelerate(&velocity, wishspeed, sv_accelerate, &dir, doom);
	//collision detection comes here
	doom->player.pos.x += velocity.x;
	doom->player.pos.y += velocity.y;
	dir_arrow(doom);
}

void	mouse_movement(t_doom *doom)
{
		int x, y;

		if(doom->mouse_switch == TRUE)
		{
			SDL_GetMouseState(&x, &y);
			doom->mouse.x = x;
			doom->mouse.y = y;
			SDL_WarpMouseInWindow(doom->rend.win, WIN_W / 2, WIN_H /2);
			SDL_ShowCursor( SDL_DISABLE );
	//		printf("m_x = %d\tm_y = %d\n", doom->mouse.x, doom->mouse.y);
		}
		else
			SDL_ShowCursor(SDL_ENABLE);
}

static void	rotate_room(t_dbg_room *room, t_debug *debug)
{
	int		i;
	double	c;
	double	s;
	int		angle;

	i = 0;
	angle = (debug->p_angle + debug->rotation) % 360;
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

void	keyevent(t_doom *doom, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
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
			 doom->debug.rotation++;
			 rotate_room(doom->room, &doom->debug);
			//rotate_player(&doom->world, &doom->mmap, 1);
			//cull_vertices(&doom->world);
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_m) //mouse_swich
		{
			ft_printf("CLICK\n");
			if(doom->mouse_switch == FALSE)
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
