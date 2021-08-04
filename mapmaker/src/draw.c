#include "doom.h"

/*
** Takes center x & y point and draws a dot.
*/

void	draw_dot(t_rend *rend, int pixel)
{
	int	r1;
	int	r3;

	r1 = pixel - WIN_W;
	r3 = pixel + WIN_W;
	rend->win_pixel_buffer[pixel] = WHITE;
	rend->win_pixel_buffer[r1] = WHITE;
	rend->win_pixel_buffer[r3] = WHITE;
	rend->win_pixel_buffer[pixel + 1] = WHITE;
	rend->win_pixel_buffer[pixel - 1] = WHITE;
}

int	ft_is_neg(double nb)
{
	unsigned long long	*x;
	int					ret;

	x = (unsigned long long *)&nb;
	ret = (*x >> 63);
	if (ret == 1)
		return (1);
	return (0);
}


float	ft_flabs(float a)
{
	if (ft_is_neg((double)a))
		a = a * (-1);
	return (a);
}

/*
** Returns step for draw_line function.
*/

float		draw_step(float dx, float dy)
{
	if (ft_flabs(dx) >= ft_flabs(dy))
		return (ft_flabs(dx));
	else
		return (ft_flabs(dy));
}

/*
** Takes two coordinates and then uses the dda algorithm to draw a line.
*/

void	draw_line(t_rend *rend, t_point start, t_point end)
{
	float		dx;
	float		dy;
	float		step;
	int			i;
	uintmax_t	pixel;

	i = 0;
	dx = (end.x - start.x);
	dy = (end.y - start.y);
	step = draw_step(dx, dy);
	dx = dx / step;
	dy = dy / step;
//	printf("dx = %f dy = %f\n", dx, dy);
	while (i <= step)
	{
		pixel = -1;
		if ((int)start.x < WIN_W && (int)start.x >= 0)
			pixel = (int)start.x + (int)start.y * WIN_W;
		printf("x = %d, y = %d, pixel = %ju\n", start.x, start.y, pixel);
		if (pixel <= WIN_MAX && pixel >= 0)
			rend->win_pixel_buffer[pixel] = GREY;
		start.x += dx;
		start.y += dy;
		i++;
	}
}




/*
void    drawpixel(int x, int y, uint32_t *buffer, uint32_t color)
{
    uint32_t    i;

    i = (WIN_W * y) + x;
//	printf("x: %d y %d\n", x, y);
    if (x < WIN_W && y < WIN_H && x >= 0 && y >= 0)
        buffer[i] = color;
}

static void    init_startingvalues(t_point p0, int *x, int *y)
{
    *x = p0.x;
    *y = p0.y;
}

static void    init_errors(t_point p0, t_point p1, int *derror, int *error)
{
    *derror = abs(p1.y - p0.y) * 2;
    *error = 0;
}

static void    init_points(t_point p0, t_point p1, t_bool *flip)
{
    *flip = FALSE;
    if (abs(p0.x - p1.x) < abs(p0.y - p1.y))
    {
        ft_swap(&p0.x, &p0.y, sizeof(int));
        ft_swap(&p1.x, &p1.y, sizeof(int));
        *flip = TRUE;
    }
    if (p0.x > p1.x)
    {
        ft_swap(&p0.x, &p1.x, sizeof(int));
        ft_swap(&p0.y, &p1.y, sizeof(int));
    }
}
*/

/*
*    Line drawing algorithm between two point coordinates.
*    Initial checks make sure that drawing works for all angles into
*    every direction. After that, drawline() plots
*    a line of pixels from [point0] to [point1].
*/
/*
void    draw_line(t_rend *rend, t_point p0, t_point p1)
{
    int        derror;
    int        error;
    int        x;
    int        y;
    t_bool    flip;

	printf("p0.x %d p0.y %d -> p1.x %d p1.y %d\n", p0.x, p0.y, p1.x, p1.y);
    init_points(p0, p1, &flip);
    init_errors(p0, p1, &derror, &error);
    init_startingvalues(p0, &x, &y);
    while (x <= p1.x && x++)
    {
        if (flip)
            drawpixel(x - 1, y, rend->win_pixel_buffer, GREY);
        else
            drawpixel(y, x - 1, rend->win_pixel_buffer, GREY);
        error += derror;
        if (error > p1.x - p0.x)
        {
            if (p1.y > p0.y)
                y += 1;
            else
                y += -1;
            error -= (p1.x - p0.x) * 2;
        }
    }
}
*/
