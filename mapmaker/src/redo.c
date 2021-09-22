#include "mapmaker.h"

/*
**
*/

void	e_redo(t_editor *edit)
{
	t_wlist	*save;

	if (edit->tail != NULL)
	{
		save = edit->tail->next;
		edit->tail->next = NULL;
		w_lstpush(&edit->head, edit->tail);
		edit->tail = save;
	}
	else
		edit->redo = FALSE;
}

/*
**
*/

void	e_del_list(t_wlist **list)
{
	t_wlist	*temp;
	t_wlist	*next;

	temp = *list;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	*list = NULL;
}
