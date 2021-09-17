#include "mapmaker.h"

void	w_lstadd(t_wlist **alst, t_wlist *new)
{
	if (!alst || !new)
		return ;
	new->next = (*alst);
	*alst = new;
}


void	w_lstdel(t_wlist **alst, void (*del)(void *, size_t))
{
	t_wlist	*temp;

	if (!alst || !del)
		return ;
	while (*alst)
	{
		temp = (*alst)->next;
	//	del((*alst)->wall, sizeof(t_wall));
		free(*alst);
		*alst = temp;
	}
	*alst = NULL;
}


void	w_lstdelone(t_wlist **alst, void (*del)(void *, size_t))
{
	if (!alst || !del)
		return ;
//	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}

void	w_lstiter(t_wlist *lst, void (*f)(t_wlist *elem))
{
	t_wlist	*temp;

	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		temp = lst->next;
		f(lst);
		lst = temp;
	}
}

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

t_wlist	*w_lstnew(void)
{
	t_wlist	*new;
	t_point	nul;

	nul.x = 0;
	nul.y = 0;
	new = (t_wlist *)malloc(sizeof(t_wlist));
	if (!(new))
		return (NULL);
	new->wall.start = nul;
	new->wall.end= nul;
	new->next = NULL;
	return (new);
}

void	w_lstpush(t_wlist **alst, t_wlist *new)
{
	t_wlist	*last;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		last = w_lstlast(*alst);
		last->next = new;
	}
	else
		*alst = new;
}

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
