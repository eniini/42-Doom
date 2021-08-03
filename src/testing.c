#include "doom.h"

t_point	px = {WIN_W/2, WIN_H/2};
t_point	p1 = {0, 0};
t_point	p2 = {0, WIN_H};
t_point	p3 = {WIN_W, WIN_H};
t_point	p4 = {WIN_W, 0};
float	counter = 0.0;

void	drawlinetest(t_buffer *buf)
{
	t_point	mp;
	counter += 0.001;
	mp.x = ft_i_lerp(p1.x, p2.x, counter);
	mp.y = ft_i_lerp(p1.y, p2.y, counter);
	draw_line(buf, px, mp, ft_color_lerp(0x006666ff, 0x00ff6666, counter));
	mp.x = ft_i_lerp(p2.x, p3.x, counter);
	mp.y = ft_i_lerp(p2.y, p3.y, counter);
	draw_line(buf, px, mp, ft_color_lerp(0x00ff6666, 0x00ffff66, counter));
	mp.x = ft_i_lerp(p3.x, p4.x, counter);
	mp.y = ft_i_lerp(p3.y, p4.y, counter);
	draw_line(buf, px, mp, ft_color_lerp(0x00ffff66, 0x0066ffff, counter));
	mp.x = ft_i_lerp(p4.x, p1.x, counter);
	mp.y = ft_i_lerp(p4.y, p1.y, counter);
	draw_line(buf, px, mp, ft_color_lerp(0x0066ffff, 0x006666ff, counter));
	if (counter >= 1.0)
		counter = 0.0f;
}

static void	tga_load_test(t_rend *renderer, t_assets *assets)
{	
	static uint32_t	x;
	static uint32_t	y;
	static float	size = 1;

	if (blit_img_scaled(assets->testimg, renderer->win_pixels, \
		(t_point){x, y}, size) < 0)
		ft_getout("blit out of bounds / Nulpointer");
	if (y < WIN_H)
	{
		if (x < WIN_W)
			x++;
		else
		{
			size -= 0.1f;
			x = 0;
			y += WIN_H / 10;
		}
	}
	else
	{
		size = 1.f;
		y = 0;
	}
}

void	dotests(t_buffer *buf, t_assets *assets)
{
	drawlinetest(buf);
	//tga_load_test(buf, assets);
	//update_boids(assets->flock, buf);
}
