#include "mapmaker.h"

void	e_draw_map(t_img *img, t_wlist *head)
{
	t_wlist	*temp;

	temp = head;
	clear_canvas(img);
	while (temp != NULL)
	{
		if (temp->wall.end.x != 0)
		{
			draw_line(img->win_buffer, temp->wall.start, temp->wall.end, GREY);
			draw_filled_circle(img->win_buffer, temp->wall.end, RADIUS, WHITE);
		}
		draw_filled_circle(img->win_buffer, temp->wall.start, RADIUS, WHITE);
		temp = temp->next;
	}
}
