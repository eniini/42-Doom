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
	result = vector2_rotate(orbiter, (t_vector){doom->player.pos.x, doom->player.pos.y, 0, 1}, doom->player.yaw);
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
	t_fvector		dir = (t_fvector){0, 0, 0, 1};
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
