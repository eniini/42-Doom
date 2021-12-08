#include "doom.h"

//*******************************************************
//	TODO:	
//
//		Mandatory:
//		-	sectors, movement between
//		-	jump (third dimension, so far only two)/
//
//		Bonus:
//		-	proper friction, now its not symmetrical
//			and does not scale with delta
//		-	bounce angle when hitting walls
//		-	diagonal input
//
//*******************************************************

float	DotProduct(t_fvector v1, t_fvector v2)
{
	return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

//this function takes in three 2d points and returns the orintation of the r point relative
//to the p and q points.
//positive for clockwise
//negative for counter clockwise
//zero for linear
int		p_orientation(t_vector p, t_vector q, t_fvector r)
{
	return((q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y));
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
	t_line	line;

	orbiter.x = doom->player.pos.x + 40;
	orbiter.y = doom->player.pos.y;
	result = vector_2drotate(orbiter, (t_vector){doom->player.pos.x, doom->player.pos.y, 0, 0}, doom->player.yaw);
	line.start.x = doom->player.pos.x;
	line.start.y = doom->player.pos.y;
	line.start.z = doom->player.pos.z;
	line.end.x = result.x;
	line.end.y = result.y;
	line.end.z = result.z;
	draw_vector_line(doom->rend.win_buffer, line, 0xFFFFFF);
}

//
//This function chekcs if vector is inside a rectangle
//that drawn around walls[i].start and walls[i].end
//returns 1 when point is in rectangle.
//returns 0 when point is not in rectangle
int		wall_hitbox(t_doom *doom, t_fvector vector, int i)
{
	int minx, miny, maxx, maxy;

	if(doom->world.room->walls[i].start.x < doom->world.room->walls[i].end.x)
	{
		minx = doom->world.room->walls[i].start.x - 1;
		maxx = doom->world.room->walls[i].end.x + 1;
	}
	else
	{
		minx = doom->world.room->walls[i].end.x - 1;
		maxx = doom->world.room->walls[i].start.x + 1;
	}
	if(doom->world.room->walls[i].start.y < doom->world.room->walls[i].end.y)
	{
		miny = doom->world.room->walls[i].start.y - 1;
		maxy = doom->world.room->walls[i].end.y + 1;
	}
	else
	{
		miny = doom->world.room->walls[i].end.y - 1;
		maxy = doom->world.room->walls[i].start.y + 1;
	}
	if(minx < vector.x && vector.x < maxx && miny < vector.y && vector.y < maxy)
		return(1);
	return(0);
}

//
//this function checks if two segments of lines intersect.
//The first segment is doom->world.room->walls[i]
//and the second segment is doom->player.pos and doom->plater.pos + velocity.
//If these segments intersect it will count as collision and
//the function will return 1.
//If no collision is detected the function will return 0
//
int		segment_intersect(t_doom *doom, t_fvector *velocity, int i)
{
	t_fvector vector, vector2;
	int ret1, ret2;

	vector.x = doom->player.pos.x - WIN_W/2;
	vector.y = doom->player.pos.y - WIN_H/2;
	vector2.x = doom->player.pos.x + velocity->x - WIN_W/2;
	vector2.y = doom->player.pos.y + velocity->y - WIN_H/2;
	vector.z = 0.f;
	vector2.z = 0.f;
	ret1 = p_orientation(doom->world.room->walls[i].start, doom->world.room->walls[i].end, vector);
	ret2 = p_orientation(doom->world.room->walls[i].start, doom->world.room->walls[i].end, vector2);
	if(ret2 == 0 )
		return(1);
	if(ret1 > 0 && ret2 > 0)
		return(0);
	if(ret1 < 0 && ret2 < 0)
		return(0);
	return(1);
}

//this function makes the player bounce off the window borders.
//Really needed only for debugging/testing purposes.
//In reality the player should not collide with the borders.
void	window_border_col(t_doom *doom, t_fvector *velocity, float bounce)
{
	if(doom->player.pos.x < 0)
	{
		doom->player.pos.x = 0;
		velocity->x = velocity->x * -bounce;
		doom->audio.boing_trigger = 1;
	}
	if(doom->player.pos.y < 0)
	{
		doom->player.pos.y = 0;
		velocity->y = velocity->y * -bounce;
		doom->audio.boing_trigger = 1;
	}
	if(doom->player.pos.x > WIN_W)
	{
		doom->player.pos.x = WIN_W;
		velocity->x = velocity->x * -bounce;
		doom->audio.boing_trigger = 1;
	}
	if(doom->player.pos.y > WIN_H)
	{
		doom->player.pos.y = WIN_H;
		velocity->y = velocity->y * -bounce;
		doom->audio.boing_trigger = 1;	
	}
}

//**
//This function checks for collision between the player and surroundings(walls).
//and manipulates velocity accordingly.
//**
void	collision(t_doom *doom, t_fvector *velocity)
{	
	float	bounce = 1;
	int		i = 0;
	int 	j = 0;

	window_border_col(doom, velocity, bounce);	
	while(i < doom->world.room->wallcount)
	{
		j = segment_intersect(doom, velocity, i);	
		if(j)
		{
			printf("COLLISION!!! WALL NUMBER %i\n", i);
			velocity->x = 0;
			velocity->y = 0;
			doom->audio.boing_trigger = TRUE;
		}
		i++;
	}
}

//This function mimics friction between the player and floor
//by reducing velocity. 
//This is a really poor way to do this, and
//is just a placeholder for a proper version.xxxx
//consider making friction non linear
void	friction(t_fvector* velocity, float delta)
{
//	printf("delta = %f\n", delta);

//	velocity->x = velocity->x * delta * 1000;
//	velocity->y = velocity->y * delta * 1000;
	if (delta) //dummy check to utilize delta parameter
		velocity->z = velocity->z;
	velocity->x = velocity->x * 0.99;	
	velocity->y = velocity->y * 0.99;	
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
		dir.x = (dir.x + cosf(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
		dir.y = (dir.y + sinf(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
	}
	if (doom->keys.down_pressed == TRUE)
	{
		dir.x = (dir.x - cosf(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
		dir.y = (dir.y - sinf(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
	}
	if (doom->keys.left_pressed == TRUE)	
	{
		dir.x = (dir.x + sinf(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
		dir.y = (dir.y - cosf(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
	}
	if (doom->keys.right_pressed == TRUE)
	{
		dir.x = (dir.x - sinf(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
		dir.y = (dir.y + cosf(doom->player.yaw * DEG_TO_RAD)) * doom->delta;
	}
//	wishspeed = sqrt(dir.x * dir.x + dir.y * dir.y);

	accelerate(&velocity, wishspeed, sv_accelerate, &dir, doom);
	collision(doom, &velocity);	
// if friction != velocity, then:
	friction(&velocity, doom->delta);	
	doom->player.pos.x += velocity.x;
	doom->player.pos.y += velocity.y;
}

/*   DELETE THIS FUNCTION LATER
void	mouse_movement(t_doom *doom)
{
		int x, y;

		if(doom->keys.mouse_switch == TRUE)
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
*/



/*	DELETE THIS FUNCTION TO HELL
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
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_m) //mouse_swich
		{
			ft_printf("CLICK\n");
			if(doom->keys.mouse_switch == FALSE)
				doom->keys.mouse_switch = TRUE;
			else
				doom->keys.mouse_switch = FALSE;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_o) //mute_switch
		{
			ft_printf("mute_switch = %d\n", doom->audio.mute_switch);
			if(doom->audio.mute_switch == FALSE)
				doom->audio.mute_switch = TRUE;
			else
				doom->audio.mute_switch = FALSE;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_t) //fps_swich
		{
			ft_printf("CLICK\n");
			if(doom->keys.fps_switch == FALSE)
				doom->keys.fps_switch = TRUE;
			else
				doom->keys.fps_switch = FALSE;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_v) //view_swich
		{
			if(doom->keys.view_switch < 2)
				doom->keys.view_switch++;
			else
				doom->keys.view_switch = 0;
		}
	}
}

*/


