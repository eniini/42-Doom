#include "doom.h"
#include <stdio.h> //tbd

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

# define RADIUS 3

# define W_BUFF_SIZE 1000

typedef struct s_mouse
{
	t_point	prev;
	t_point	new;
}				t_mouse;

typedef struct s_wall
{
	t_point	start;
	t_point	end;
}			t_wall;

typedef struct s_buf
{
	t_wall	*walls;
	int		i;
	int		finished;
}			t_buf;

typedef struct s_editor
{
	t_buf	*output;
	t_buf	*working;
	t_buf	*undo;
	t_bool	cnct;
	t_bool	redo;
}			t_editor;

typedef struct s_img
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
}					t_img;

void	mouse_click(SDL_Event e, t_img *img);
void	key_events(SDL_Event e, t_img *img);

void	init_editor(t_img *img);
void	clear_canvas(t_img *img);
void	save_map(t_wall *src, t_wall *dest, int size);
void	draw_emap(t_img *img, t_buf *output);
//void	draw_map(t_img *img, t_editor *edit);
void	set_walls(t_point pixel, t_img *img, t_buf *buf);
void	draw_button(int y_start, t_img *img, uint32_t colour);
//void	set_walls(t_point pixel, t_img *img, t_editor *edit);
void	die(char *reason);

void	undo_last(t_img *img);
void	redo_last(t_img *img);

void	event_clear(t_img *img);

void	working_to_output(t_editor *edit);
void	working_to_undo(t_editor *edit);
void	undo_to_working(t_editor *edit);
void	undo_to_output(t_editor *edit);

//void	undo_last(t_img *img);
