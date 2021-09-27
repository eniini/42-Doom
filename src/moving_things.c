#include "doom.h"

float	DotProduct(t_vector3 v1, t_vector3 v2)
{
	return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

//**
//This accelerate function is from quake source code.
//**
void	accelerate (t_vector3 *velocity, float wishspeed, float sv_accelerate, t_vector3 *wishdir, t_doom *doom)
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


// sv_accelerate is constant
void	physics(t_doom *doom)
{
	static int		ticks;
	static int		prevtics;
	static t_vector3		velocity;
	float			wishspeed = 50;
	t_vector3		dir = (t_vector3){0, 0, 0};
	float sv_accelerate = 5;
	prevtics = ticks;
	ticks = SDL_GetTicks();
	doom->delta = (ticks - prevtics) / 1000.0;

	if (doom->keys.up_pressed == TRUE)
		dir.y -= doom->delta * 1;
	if (doom->keys.down_pressed == TRUE)
		dir.y += doom->delta * 1;
	if (doom->keys.left_pressed == TRUE)	
		dir.x -= doom->delta * 1;
	if (doom->keys.right_pressed == TRUE)
		dir.x += doom->delta * 1;
//	wishspeed = sqrt(dir.x * dir.x + dir.y * dir.y);
	accelerate(&velocity, wishspeed, sv_accelerate, &dir, doom);
	//collision detection comes here
	doom->player.pos.x += velocity.x;
	doom->player.pos.y += velocity.y;

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
			rotate_player(&doom->world, &doom->mmap, 1);
			cull_vertices(&doom->world);
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_t) //fps_swich
		{
			ft_printf("CLICK\n");
			if(doom->fps_switch == FALSE)
				doom->fps_switch = TRUE;
			else
				doom->fps_switch = FALSE;
		}
		int x, y;
		SDL_GetMouseState(&x, &y);
		printf("m_x = %d\tm_y = %d\n", x, y);
	}
}

