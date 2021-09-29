#include "mapmaker.h"

/*
** Adds the new wlist item to the front of the list.
*/
void	w_lstadd(t_wlist **alst, t_wlist *new)
{
	if (!alst || !new)
		return ;
	new->next = (*alst);
	new->prev = NULL;
	*alst = new;
}

/*
** Returns the last wlist item on the list.
*/
t_wlist	*w_lstlast(t_wlist *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
** Creates a new, formatted to 0's and NULLs, wlist item.
*/
t_wlist	*w_lstnew(void)
{
	t_wlist		*new;
	t_vector	nul;

	nul.x = 0;
	nul.y = 0;
	new = (t_wlist *)malloc(sizeof(t_wlist));
	if (!(new))
		return (NULL);
	new->wall.start = nul;
	new->wall.end= nul;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/*
** Adds the new wlist item to the back of the list.
*/
void	w_lstpush(t_wlist **alst, t_wlist *new)
{
	t_wlist	*last;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		last = w_lstlast(*alst);
		new->prev = last;
		last->next = new;
	}
	else
		*alst = new;
}

/*
** Returns the size of a list.
*/
int	w_lstsize(t_wlist *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
