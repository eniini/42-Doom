#include "doom.h"

#define PRINT_OFFSET 0x20

/*
*	Write onto given buffer using given texture atlas/symbol lookup table
*/
void	write_onto_buffer(t_buffer *buf, t_font	*font, char	*msg, t_pixel pos)
{
	int			i;
	int			c;
	t_square	crop;

	i = 0;
	while (msg[i] != 0)
	{
		c = msg[i] - PRINT_OFFSET;
		crop.start.x = font->symlist[c].xpos;
		crop.start.y = font->symlist[c].ypos;
		crop.end.x = font->symlist[c].xpos + font->pitch;
		crop.end.y = (font->symlist[c].ypos + font->size);
		blit_cropped(font->atlas, crop, buf, pos);
		pos.x += font->pitch;
		i++;
	}
}

//setup doom->symbol to hold correct offset for each letter in the texture atlas
//pitch is atlas->width / letters per line
void	init_font_atlas(t_doom *doom)
{
	int	i;
	int	j;

	if (!doom->font.atlas)
		ft_getout("failed to find a fond atlas!");
	doom->font.size = 20;
	doom->font.pitch = doom->font.atlas->w / 16;
	doom->font.symlist = malloc(sizeof(t_sym) * 100);
	i = 0;
	j = 0;
	while (i < 95)
	{
		doom->font.symlist[i].value = i + PRINT_OFFSET;
		doom->font.symlist[i].xpos = i % 16 * 16;
		doom->font.symlist[i].ypos = j * doom->font.size;
		i++;
		if (!(i % 16))
			j++;
	}
}
