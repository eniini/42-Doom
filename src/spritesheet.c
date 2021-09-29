#include "doom.h"

/*
*	[count] is the number of sprites generated from the given image.
*	[dimensions] is the length and width of each generated sprite.
*	Creates a struct that stores all the necessary data to blit individual
*	sprites from the given spritesprite image.
*/
t_sprite	*create_sprite(t_img *img, uint32_t count, t_pixel dimensions)
{
	t_sprite	*sprite;
	uint32_t	y;
	uint32_t	x;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (!sprite || !img)
		return (NULL);
	sprite->img = img;
	sprite->width = 0;
	sprite->sprite_count = count;
	y = 0;
	while (dimensions.y * y <= img->h)
	{
		x = 0;
		while (dimensions.x * x <= img->w)
			x++;
		if (x > sprite->width)
			sprite->width = x;
		y++;
	}
	sprite->sprite_w = img->w / sprite->width;
	sprite->sprite_h = img->h / y;
	img = NULL;
	return (sprite);
}

/*
*	Blits frame number [i] from the given spritesheet [sprite] onto the buffer
*	coordinates given as t_pixel [start].
*/
t_bool	blit_sprite(t_sprite *sprite, t_buffer *buf, int i, t_pixel start)
{
	uint32_t	x;
	uint32_t	y;

	if (!sprite || !sprite->img || !sprite->img->px || !buf)
		return (FALSE);
	if (start.x > buf->w || start.y > buf->h)
		return (FALSE);
	y = 0;
	while ((y + start.y) <= buf->h && y < sprite->sprite_h)
	{
		x = 0;
		while ((x + start.y) <= buf->w && x < sprite->sprite_w)
		{
			buf->px[((y + start.y) * buf->w) + x + start.x] = \
			sprite->img->px[(((i / sprite->width) * \
					sprite->sprite_h + y) * sprite->img->w) + \
			((i % sprite->width) * sprite->sprite_w + x)];
			x++;
		}
		y++;
	}
	return (TRUE);
}
