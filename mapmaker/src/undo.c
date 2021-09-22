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

	if (edit->clear == FALSE)
	{
		if (!edit->head)
			return ;
		last = w_lstlast(edit->head);
		if (last == edit->head)
		{
			w_lstadd(&edit->tail, last);
			edit->head = NULL;
			return ;
		}
		temp = last->prev;
		w_lstadd(&edit->tail, last);
		temp->next = NULL;
		//	printf("tail:\n");
		//	printf_head(edit->tail);
		//	printf("head:\n");
		//	printf_head(edit->head);
		edit->redo = TRUE;
	}
	else
	{
		if (!edit->tail)
			return ;
		edit->head = edit->tail;
		edit->tail = NULL;
		edit->redo = FALSE;
		edit->clear = FALSE;
	}
}
