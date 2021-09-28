#include "mapmaker.h"

/*
** Deletes a list by taking a pointer to the list and then cycling
** through until all content has been freed. At last, the pointer
** to the beginning of the list is set to NULL.
*/
void	w_del_list(t_wlist **list)
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
