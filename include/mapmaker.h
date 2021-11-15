#ifndef MAPMAKER_H
# define MAPMAKER_H

# include "doom.h"

/*
** Button size refers to the pizels of the square-shaped button.
** Button_X is the starting line of each button on the x-axis.
** An individual button will then correlate with a y-axis
** position.
*/

# define TBAR_W 100
# define BUTTON_SIZE 40
# define BUTTON_X 20
# define BUTTON_SAVE 50
# define BUTTON_CNCT 100
# define BUTTON_UNDO 150

# define RADIUS 2

# define W_BUFF_SIZE 1000

typedef t_line	t_wall;

typedef struct s_wlist
{
	t_wall			wall;
	struct s_wlist	*next;
	struct s_wlist	*prev;
}					t_wlist;

typedef struct s_mouse
{
	t_vector	prev;
	t_vector	new;
}				t_mouse;

typedef struct s_editor
{
	t_wlist	*head;
	t_wlist	*tail;
	t_wlist	*current;
	t_bool	cnct;
	t_bool	redo;
	t_bool	clear;
}			t_editor;

typedef struct s_e_img
{
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	void			*win_pixels;
	t_buffer		*win_buffer;
	int				win_pixel_pitch;
	t_bool			run;
	t_mouse			mouse;
	t_editor		*edit;
}					t_e_img;

void	e_mouse(SDL_Event e, t_e_img *img);
void	e_keys(SDL_Event e, t_e_img *img);

void	e_init_editor(t_e_img *img);
void	e_clear_canvas(t_e_img *img);
void	e_draw_button(int y_start, t_e_img *img, uint32_t colour);
//void	die(char *reason);

// lists

void	w_lstadd(t_wlist **alst, t_wlist *new);
void	w_lstiter(t_wlist *lst, void (*f)(t_wlist *elem));
t_wlist	*w_lstlast(t_wlist *lst);
t_wlist	*w_lstnew(void);
void	w_lstpush(t_wlist **alst, t_wlist *new);
int		w_lstsize(t_wlist *lst);
void	w_del_list(t_wlist **list);

void	e_wall_add(t_vector pixel, t_e_img *img, t_editor *edit);
void	e_draw_map(t_e_img *img, t_wlist *head);
void	e_undo(t_e_img *img, t_editor *edit);
void	e_printf_head(t_wlist *head);
void	e_redo(t_editor *edit);
void	e_clear(t_e_img *img, t_editor *edit);

#endif
