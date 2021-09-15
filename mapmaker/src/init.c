#include "mapmaker.h"


/*
** Initialises the points in the buffer to 0.
*/

void	init_points(t_img *img)
{
	int		i;
	t_point	nul;

	i = 0;
	nul.x = 0;
	nul.y = 0;
	while (i <= W_BUFF_SIZE)
	{
		img->edit->output->walls[i].start = nul;
		img->edit->output->walls[i].end = nul;
		img->edit->working->walls[i].start = nul;
		img->edit->working->walls[i].end = nul;
		img->edit->undo->walls[i].start = nul;
		img->edit->undo->walls[i].end = nul;
		i++;
	}
}


/*
** Initialises buttons onto the toolbar.
*/

void	init_buttons(t_img *img)
{
	draw_button(BUTTON_SAVE, img, GREEN);
	draw_button(BUTTON_CNCT, img, RED);
	draw_button(BUTTON_UNDO, img, TEAL);
}

/*
** Initialises the buf structs for output, working, and undo.
*/

t_buf	*init_buf(t_buf *buf)
{
	buf = ft_calloc(1, sizeof(t_buf));
	if (!buf)
		return (NULL);
	buf->walls = ft_calloc(W_BUFF_SIZE, sizeof(t_wall));
	if (!buf->walls)
		return (NULL);
	buf->finished = -1;
	buf->i = 0;
	return (buf);
}

/*
** Initialises the "edit" struct, forms the toolbar, and calls a button drawing
** function.
*/

void	init_editor(t_img *img)
{
	int			i;
	int			j;
	uint32_t	pixel;

	img->edit = ft_calloc(1, sizeof(t_editor));
	if (!img->edit)
		die("Malloc error.");
	img->edit->output = init_buf(img->edit->output);
	img->edit->working = init_buf(img->edit->working);
	img->edit->undo = init_buf(img->edit->undo);
	if (!img->edit->output | !img->edit->working | !img->edit->undo)
		die("Malloc error.");
	j = 0;
	ft_bzero(img->win_buffer->pixels, WIN_MAX * sizeof(uint32_t));
	while (j <= WIN_H)
	{
		i = 0;
		while (i <= TBAR_W)
		{
			pixel = j * WIN_W + i;
			img->win_buffer->pixels[pixel] = BLUE;
			i++;
		}
		j++;
	}
	init_buttons(img);
	init_points(img);
	img->edit->cnct = TRUE;
	img->edit->redo = FALSE;
}
/*
void	clear_buffer(t_img *img)
{
	int			i;

	i = 0;
	while (i < img->edit->i)
	{
		img->edit->w_buffer[i].start.x = 0;
		img->edit->w_buffer[i].start.y = 0;
		img->edit->w_buffer[i].end.x = 0;
		img->edit->w_buffer[i].end.y = 0;
		i++;
	}
	img->edit->i = 0;
}
*/
