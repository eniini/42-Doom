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

/*
** Saves the clicked spot on the map into the t_wall structs in a linked list.
** First checks if the mouse prev and new are not the same. Then, it checks if
** the current wlist item exists; if not, it'll create one and depending
** on whether the connect status is on or off, will assign the starting point
** either as the previous place the mouse clicked or the new given pixel.
** Afterwards, it pushes the item at the back of the list, or at the head if
** there is no list. If the item exists, the clicked pixel will be assigned
** as the end point, and the pointer to the current one will move on.
*/

// TODO make a check this doesn't grow too big

void	e_wall_add(t_vector pixel, t_e_img *img, t_editor *edit)
{
	t_wlist	*new;

//	printf("prev xy %d, %d; new xy %d, %d\n", img->mouse.prev.x, img->mouse.prev.y,
//		img->mouse.new.x, img->mouse.new.y);
	if ((img->mouse.new.x != img->mouse.prev.x
		|| img->mouse.new.y != img->mouse.prev.y))
	{
		if (edit->current == NULL)
		{
			new = w_lstnew();
			if (!new)
				ft_getout("Malloc failure in linked list.");
			if (edit->head == NULL)
				edit->head = new;
			else
				w_lstpush(&edit->head, new);
			if (new->prev != NULL && edit->cnct == TRUE)
			{
				new->wall.start = new->prev->wall.end;
				new->wall.end = pixel;
			}
			else
				new->wall.start = pixel;
			edit->current = new;
			if (edit->current != edit->head && edit->cnct == TRUE)
				edit->current = edit->current->next;
		}
		else
		{
			edit->current->wall.end = pixel;
			edit->current = edit->current->next;
		}
		img->mouse.prev = pixel;
	}
//	printf_head(edit->head);
}
