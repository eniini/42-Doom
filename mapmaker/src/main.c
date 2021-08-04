#include "doom.h"

/*
*	Todo:	read up on windowflags in case we could have additional features
*			do we need sethint() and should it be to linear or nearest?
*			same thing with rendermodes, pixelformat etc.
*			blending is only needed if we work with multiple texture layers
*/
void	init(t_rend *renderer)
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
		SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!renderer->win_tex)
		ft_getout(SDL_GetError());
	//if ((SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND)))
	//	ft_getout(SDL_GetError());
	renderer->run = TRUE;
	renderer->mouse.line = -1;
}

void	cleanup(t_rend *renderer)
{
	SDL_DestroyTexture(renderer->win_tex);
	SDL_DestroyRenderer(renderer->rend);
	SDL_DestroyWindow(renderer->win);
	SDL_Quit();
}

void	loop(t_rend *renderer)
{
	SDL_Event		e;

	while (SDL_PollEvent(&e))
	{
		if (e.window.event == SDL_WINDOWEVENT_CLOSE)
			renderer->run = FALSE;
		if (e.button.state == SDL_PRESSED)
			mouse_click(e, renderer);
	}
	if (SDL_LockTexture(renderer->win_tex, NULL, \
		(void **)&renderer->win_pixel_array, &renderer->win_pixel_pitch) < 0)
		ft_getout(SDL_GetError());
	ft_memcpy(renderer->win_pixel_array, renderer->win_pixel_buffer, \
	WIN_H * renderer->win_pixel_pitch);
	SDL_UnlockTexture(renderer->win_tex);
	if (SDL_RenderCopy(renderer->rend, renderer->win_tex, NULL, NULL) < 0)
		ft_getout(SDL_GetError());
	SDL_RenderPresent(renderer->rend);
}

int main(void)
{
	t_rend	renderer;
	
	ft_bzero(&renderer, sizeof(t_rend));
	renderer.win_pixel_buffer = ft_memalloc(WIN_H * WIN_W);
	renderer.win_pixel_array = ft_memalloc(WIN_H * WIN_W);
	init(&renderer);
	while (renderer.run)
		loop(&renderer);
	cleanup(&renderer);
	return (0);
}