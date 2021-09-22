#include "mapmaker.h"


/*
** Goes through the list to find the last and second to last
** items of the list. The second-to-last's next gets set to NULL,
** while the last item gets put at the top of the tail list
** pointer.
*/

void	e_undo_last(t_editor *edit)
{
	t_wlist	*temp;
	t_wlist	*last;

//	temp = edit->head;
	if (!edit->head)
		return ;
	last = w_lstlast(edit->head);
	if (last == edit->head)
	{
		w_lstadd(&edit->tail, last);
		edit->head = NULL;
		return ;
	}
/*	if (temp->next != NULL)
	{
		while (temp->next->next != NULL)
			temp = temp->next;
		temp->next = NULL;
	}*/
	temp = last->prev;
	w_lstadd(&edit->tail, last);
	temp->next = NULL;
	printf("tail:\n");
	printf_head(edit->tail);
	printf("head:\n");
	printf_head(edit->head);
	edit->redo = TRUE;
}

/*
** In the case of a undo/redo event, the output of either the
** undo or the working buffer is put out on the output. The
** "redo" flag signifies that a redo action is possible. If a
** disconnected wall piece is undo'd, it is fully erased.
*/

void	undo_last(t_img *img)
{
	t_point	nul;
	int		i;

	i = img->edit->undo->i;
	nul.x = 0;
	nul.y = 0;
	if (img->edit->cnct == FALSE)
	{
		if (img->edit->undo->walls[i].start.x == 0)
		{
			img->edit->undo->i--;
			i = img->edit->undo->i;
			img->edit->undo->walls[i].start = nul;
			img->edit->undo->walls[i].end = nul;
		}
		else
			img->edit->undo->walls[i].start = nul;
		img->edit->undo->finished = -1;
	}
	undo_to_output(img->edit);
	draw_emap(img, img->edit->output);
	img->edit->redo = TRUE;
}

void	redo_last(t_img *img)
{
	working_to_output(img->edit);
	draw_emap(img, img->edit->output);
	img->edit->redo = FALSE;
}
