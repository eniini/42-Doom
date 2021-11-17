#include "doom.h"

/*
* 	Note:
*	Unless we create a font compiler in the future, all of the values
*	regarding font atlas properties are hardcoded into the function calls.
*/

/*
*	Creates a one-time use struct that blits the contents of [str] into a buffer
*	with the specified [color] and coordinates [pos].
*/
t_msg	*create_msg(char *str, uint32_t color, t_pixel pos)
{
	t_msg	*msg;

	msg = (t_msg *)malloc(sizeof(t_msg));
	if (!msg)
		return (NULL);
	msg->str = ft_strdup(str);
	if (!msg->str)
	{
		free(msg);
		return (NULL);
	}
	msg->color = color;
	msg->pos = pos;
	return (msg);
}

/*
*	Deallocates msg struct and its contents.
*/
void	delete_msg(t_msg *msg)
{
	if (msg != NULL)
	{
		free(msg->str);
		free(msg);
		msg = NULL;
	}
}

/*
*	Variation of blit_crop where each pixel inside the square [s] of the
*	font atlas is checked to be a nonzero value (part of a symbol) and copied
*	into given [buffer] in the color determined beforehand.
*/
static int	blit_fontsym(t_font *font, t_square s, t_buffer *buf, t_pixel start)
{
	uint32_t	x;
	uint32_t	y;

	if (!font || !buf)
		return (-1);
	if (start.x > buf->w || start.y > buf->h)
		return (-1);
	y = 0;
	while ((y + start.y) < buf->h && (y + s.start.y) < s.end.y)
	{
		x = 0;
		while ((x + start.x) < buf->w && (x + s.start.x) < s.end.x)
		{
			if (font->atlas->px[((y + s.start.y) * font->atlas->w) + \
				(x + s.start.x)] == 0xFFFFFFFF)
			{
				buf->px[((y + start.y) * buf->w) + x + start.x] = font->color;
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
*	Write onto given buffer [buf] using given font [f] the message [msg] that
*	will be de-allocated after blitting its content into the buffer as symbols.
*/
void	write_to_buffer(t_buffer *buf, t_font *f, t_msg *msg)
{
	int			i;
	int			c;
	t_square	crop;

	i = 0;
	if (!msg || !f)
		return ;
	while (msg->str[i] != '\0' && (msg->str[i] >= 0x20 && msg->str[i] <= 0x7e))
	{
		c = msg->str[i] - PRINTABLE_CHAR_OFFSET;
		crop.start.x = f->symlist[c].xpos;
		crop.start.y = f->symlist[c].ypos;
		crop.end.x = f->symlist[c].xpos + f->stride;
		crop.end.y = (f->symlist[c].ypos + f->size);
		f->color = msg->color;
		if (blit_fontsym(f, crop, buf, msg->pos))
			ft_getout("invalid blit target/source or msg position OOB");
		msg->pos.x += f->stride;
		i++;
	}
	delete_msg(msg);
}

/*
*	Inits font to hold a correct offset for each letter in the texture atlas.
*	[fsize] is the font size / vertical length of each symbol
*	[atlas_w] is the width of the atlas image
*	[s_rowc] is the count of symbols per row in the atlas
*/
void	init_font_atlas(t_font *f, uint fsize, uint atlas_w, uint s_rowc)
{
	int	i;
	int	j;

	if (!f->atlas)
		ft_getout("failed to find a fond atlas!");
	f->size = fsize;
	f->stride = atlas_w / s_rowc;
	f->symlist = ft_memalloc(sizeof(t_sym) * PRINTABLE_CHAR_COUNT + 1);
	if (!f->symlist)
		ft_getout("malloc failure @init_font_atlas()");
	i = 0;
	j = 0;
	while (i < PRINTABLE_CHAR_COUNT)
	{
		f->symlist[i].value = i + PRINTABLE_CHAR_OFFSET;
		f->symlist[i].xpos = (i % s_rowc) * f->stride;
		f->symlist[i].ypos = j * f->size;
		i++;
		if (!(i % s_rowc))
			j++;
	}
}
