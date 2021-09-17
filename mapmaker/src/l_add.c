#include "mapmaker.h"

void	printf_head(t_wlist *head)
{
	t_wlist	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("start: %d, %d //// end: %d, %d\n", temp->wall.start.x, temp->wall.start.y,
			temp->wall.end.x, temp->wall.end.y);
		temp = temp->next;
	}
	printf("/////\n");
}

void	l_clicked(t_point pixel, t_img *img, t_editor *edit)
{
	t_wlist	*new;
	t_wlist	*temp;
	t_point	nul;

	nul.x = 0;
	nul.y = 0;
	if (edit->i < W_BUFF_SIZE && (edit->finished == -1
		|| (img->mouse.new.x != img->mouse.prev.x
		|| img->mouse.new.y != img->mouse.prev.y)))
	{
		img->mouse.prev = pixel;
		if (edit->current == NULL)
		{
			new = w_lstnew();
			if (!new)
				die("Malloc failure in linked list.");
			new->wall.start = pixel;
			if (edit->head == NULL)
				edit->head = new;
			else
				w_lstpush(&edit->head, new);
			edit->current = new;
		}
		else
		{
			edit->current->wall.end = pixel;
			if (edit->cnct == TRUE)
			{
				new = w_lstnew();
				if (!new)
					die("Malloc failure in linked list.");
				new->wall.start = pixel;
				edit->current->next = new;
			}
			edit->current = edit->current->next;
		}
	}
//	printf_head(edit->head);
}
