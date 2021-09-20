#include "doom.h"

/*
*	Todo:	read up on windowflags in case we could have additional features
*			Q:do we need sethint() and should it be to linear or nearest?
*			same thing with rendermodes, pixelformat etc.
*			A:Currently we don't use any SDL texture transformation funcs so its
*			probably not needed!
*			blending is only needed if we work with multiple texture layers
*			(and if we want to blend them together)
*/

void		init_player(t_doom *doom)
{
	doom->player.pos.x = 100;
	doom->player.pos.y = 100;
	doom->keys.up_pressed = FALSE;
	doom->keys.down_pressed = FALSE;
	doom->keys.left_pressed = FALSE;
	doom->keys.right_pressed = FALSE;
	doom->fps_switch = FALSE;

}

static void	init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_getout(SDL_GetError());
	doom->rend.win = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (!doom->rend.win)
		ft_getout(SDL_GetError());
	doom->rend.renderer = SDL_CreateRenderer(doom->rend.win, -1, \
		SDL_RENDERER_ACCELERATED);
	if (!doom->rend.renderer)
		ft_getout(SDL_GetError());
	doom->rend.win_tex = SDL_CreateTexture(doom->rend.renderer, \
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!doom->rend.win_tex)
		ft_getout(SDL_GetError());
	doom->rend.run = TRUE;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048 ) != 0)
		ft_getout(SDL_GetError());
	init_audio(&doom->audio);
	init_player(doom);
}

static void	cleanup(t_doom *doom)
{
	free(doom->world.verts);
	free(doom->world.p_verts);
	free(doom->world.v_walls);
	SDL_DestroyTexture(doom->rend.win_tex);
	SDL_DestroyRenderer(doom->rend.renderer);
	SDL_DestroyWindow(doom->rend.win);
	free(doom->rend.win_buffer->pixels);
	free(doom->rend.win_buffer);
	audio_cleanup(&doom->audio);
	cleanup_tests(&doom->assets);
	Mix_Quit();
	SDL_Quit();
}

void	physics(t_doom *doom)
{
	static int		ticks;
	static int		prevtics;
	double			delta;
	int				velocity = 100;
	prevtics = ticks;
	ticks = SDL_GetTicks();
	delta = (ticks - prevtics) / 1000.0;

	if (doom->keys.up_pressed == TRUE)
		doom->player.pos.y -= delta * velocity;
	if (doom->keys.down_pressed == TRUE)
		doom->player.pos.y += delta * velocity;
	if (doom->keys.left_pressed == TRUE)
		doom->player.pos.x -= delta * velocity;
	if (doom->keys.right_pressed == TRUE)
		doom->player.pos.x += delta * velocity;
}

static void	keyevent(t_doom *doom, SDL_Event *e)
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
		//PROJECTION STUFF
		if (e->key.keysym.sym == SDLK_r) //testing map/player rotation
			rotate_player(&doom->world, &doom->mmap, 1);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_w)
			apply_movement(&doom->world, (t_vert){0, 1});
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_s)
			apply_movement(&doom->world, (t_vert){0, -1});
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_a)
			apply_movement(&doom->world, (t_vert){1, 0});
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_d)
			apply_movement(&doom->world, (t_vert){-1, 0});
		cull_vertices(&doom->world);
		apply_perspective(&doom->world);
		//PROJECTION STUFF
	}
}
/*
*	Note about SDL_LockTexture: void **pixels is 'filled in', meaning that SDL
*	creates its own allocated pixel buffer thats returned to the given pointer.
*	This is why you need to query for the pixel_pitch too since its the only
*	way to know the 1-directional pitch of the created buffer.
*/
static void	loop(t_doom	*doom)
{
	SDL_Event	e;

	ft_bzero(doom->rend.win_buffer->pixels, WIN_H * WIN_W * sizeof(uint32_t));
	keyevent(doom, &e);
	physics(doom);
	dotests(doom);
	audios(&doom->audio);
	draw_circle(doom->map.mapbuf, (t_point){(int)doom->player.pos.x, (int)doom->player.pos.y}, 10, MMAP_C_PLAYER);
	if (SDL_LockTexture(doom->rend.win_tex, NULL, \
		&doom->rend.win_pixels, &doom->rend.win_pixel_pitch) < 0)
		ft_getout(SDL_GetError());
	ft_memcpy(doom->rend.win_pixels, doom->rend.win_buffer->pixels, \
	WIN_H * doom->rend.win_pixel_pitch);
	SDL_UnlockTexture(doom->rend.win_tex);
	if (SDL_RenderCopy(doom->rend.renderer, doom->rend.win_tex, NULL, NULL) < 0)
		ft_getout(SDL_GetError());
	SDL_RenderPresent(doom->rend.renderer);
	fps_counter(&doom->global_fps);
	if (doom->fps_switch == TRUE)
		SDL_Delay(40);
}

int	main(void)
{
	t_doom		doom;

	doom.rf = (t_rf){0, 18, NULL, 0};
	ft_bzero(&doom.rend, sizeof(t_rend));
	doom.rend.win_buffer = (t_buffer *)malloc(sizeof(t_buffer));
	if (!doom.rend.win_buffer)
		ft_getout("failed to initialize main buffer");
	doom.rend.win_buffer->w = WIN_W;
	doom.rend.win_buffer->h = WIN_H;
	doom.rend.win_buffer->pixels = (uint32_t *)ft_memalloc(WIN_H * WIN_W);
	init(&doom);
	init_tests(&doom);
	while (doom.rend.run)
		loop(&doom);
	cleanup(&doom);
	return (0);
}
