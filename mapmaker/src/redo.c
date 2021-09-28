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
		edit->current = edit->tail;
		edit->tail = save;
	}
	else
		edit->redo = FALSE;
}
