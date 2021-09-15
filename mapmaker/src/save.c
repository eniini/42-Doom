#include "mapmaker.h"

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

/*
** Working to output.
*/

void	working_to_output(t_editor *edit)
{
	int	i;

	i = ft_max(edit->working->i, edit->output->i);
	save_map(edit->working->walls, edit->output->walls, i);
	edit->output->i = edit->working->i;
	edit->output->finished = edit->working->finished;
}

/*
** Working to undo.
*/

void	working_to_undo(t_editor *edit)
{
	int	i;

	i = ft_max(edit->working->i, edit->undo->i);
	save_map(edit->working->walls, edit->undo->walls, i);
	edit->undo->i = edit->working->i;
	edit->undo->finished = edit->working->finished;
}

void	undo_to_working(t_editor *edit)
{
	int	i;

	i = ft_max(edit->working->i, edit->undo->i);
	save_map(edit->undo->walls, edit->working->walls, i);
	edit->working->i = edit->undo->i;
	edit->working->finished = edit->undo->finished;
}

void	undo_to_output(t_editor *edit)
{
	int	i;

	i = ft_max(edit->undo->i, edit->output->i);
	save_map(edit->undo->walls, edit->output->walls, i);
	edit->output->i = edit->undo->i;
	edit->output->finished = edit->undo->finished;
}

/*
** Saves wall points across buffers.
*/

void	save_map(t_wall *src, t_wall *dest, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		dest[i].start = src[i].start;
		dest[i].end = src[i].end;
		i++;
	}
}
