#include "doom.h"

/*
*	Todo:	read up on windowflags in case we could have additional features
*			do we need sethint() and should it be to linear or nearest?
*			same thing with rendermodes, pixelformat etc.
*			blending is only needed if we work with multiple texture layers
*/
static void	init(t_rend *renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_getout(SDL_GetError());
	renderer->win = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (!renderer->win)
		ft_getout(SDL_GetError());
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	renderer->rend = SDL_CreateRenderer(renderer->win, -1, \
		SDL_RENDERER_ACCELERATED);
	if (!renderer->rend)
		ft_getout(SDL_GetError());
	renderer->win_tex = SDL_CreateTexture(renderer->rend, \
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!renderer->win_tex)
		ft_getout(SDL_GetError());
	//if ((SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND)))
	//	ft_getout(SDL_GetError());
	renderer->run = TRUE;

	//we might need to call mix_init(MIX_INIT_MP3/OGG) if we want to use compressed files
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048 ) != 0)
		ft_getout(SDL_GetError());
}

static void	cleanup(t_rend *renderer, t_assets *assets)
{
	SDL_DestroyTexture(renderer->win_tex);
	SDL_DestroyRenderer(renderer->rend);
	SDL_DestroyWindow(renderer->win);

	free(renderer->win_buffer->pixels);
	free(renderer->win_buffer);
	//free(renderer->win_pixels);
	free(assets->testimg->data);
	free(assets->testimg);

	Mix_Quit();
	SDL_Quit();
}

/*
*	Note about SDL_LockTexture: void **pixels is 'filled in', meaning that SDL
*	creates its own allocated pixel buffer thats returned to the given pointer.
*	This is why you need to query for the pixel_pitch too since its the only
*	way to know the 1-directional pitch of the created buffer.
*/
static void	loop(t_rend *renderer, t_assets *assets)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.window.event == SDL_WINDOWEVENT_CLOSE)
			renderer->run = FALSE;
	}
	//ft_bzero(renderer->win_pixels, WIN_H * WIN_W * sizeof(uint32_t));
	ft_bzero(renderer->win_buffer->pixels, WIN_H * WIN_W * sizeof(uint32_t));
	dotests(renderer->win_buffer, assets);
	if (SDL_LockTexture(renderer->win_tex, NULL, \
		&renderer->win_pixels, &renderer->win_pixel_pitch) < 0)
		ft_getout(SDL_GetError());
	ft_memcpy(renderer->win_pixels, renderer->win_buffer->pixels, \
	WIN_H * renderer->win_pixel_pitch);
	SDL_UnlockTexture(renderer->win_tex);
	if (SDL_RenderCopy(renderer->rend, renderer->win_tex, NULL, NULL) < 0)
		ft_getout(SDL_GetError());
	SDL_RenderPresent(renderer->rend);
}

int	main(void)
{
	t_rend		renderer;
	t_assets	assets;

	ft_bzero(&renderer, sizeof(t_rend));
	init_tests(&assets);
	renderer.win_buffer = (t_buffer *)malloc(sizeof(t_buffer));
	if (!renderer.win_buffer)
		ft_getout("failed to initialize main buffer");
	renderer.win_buffer->w = WIN_W;
	renderer.win_buffer->h = WIN_H;
	renderer.win_buffer->pixels = (uint32_t *)ft_memalloc(WIN_H * WIN_W);
	//renderer.win_pixels = (uint32_t *)ft_memalloc(WIN_H * WIN_W);
	init(&renderer);
	while (renderer.run)
		loop(&renderer, &assets);
	cleanup(&renderer, &assets);
	return (0);
}
