#include "mapmaker.h"

/*
** Takes segments from the "tail" list and adds them back
** onto the "head", thus redoing what has been undone.
** If the tail is empty, the redo flag is set to FALSE,
** as no redo actions can be taken.
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
** Deletes a list by taking a pointer to the list and then cycling
** through until all content has been freed. At last, the pointer
** to the beginning of the list is set to NULL.
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
