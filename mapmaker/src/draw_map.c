#include "mapmaker.h"

/*
** Clears the canvas for drawing.
*/
void	e_clear_canvas(t_e_img *img)
{
	int			i;
	int			j;
	uint32_t	pixel;

	j = 0;
	while (j < WIN_H)
	{
		i = TBAR_W;
		while (i < WIN_W)
		{
			pixel = j * WIN_W + i;
			img->win_buffer->px[pixel] = C_BLACK;
			i++;
		}
		j++;
	}
}

/*
** Draws the map onto the canvas. Loops through the list and places
** dots at the start and end points (if they exist), and then, if
** both exist, draws a line between them. Stops as the list ends at NULL.
*/

void	e_draw_map(t_e_img *img, t_wlist *head)
{
	t_wlist	*temp;

	temp = head;
	e_clear_canvas(img);
	while (temp != NULL)
	{
		if (temp->wall.end.x != 0)
		{
			draw_line(img->win_buffer, temp->wall.start, temp->wall.end, C_GREY);
			draw_filled_circle(img->win_buffer, temp->wall.end, RADIUS, C_WHITE);
		}
		draw_filled_circle(img->win_buffer, temp->wall.start, RADIUS, C_WHITE);
		temp = temp->next;
	}
}
