//COMPILE WITH
//gcc proj_testing.c proj_helper.c -Wall -Wextra -Werror `libSDL2/bin/sdl2-config --cflags --libs` -L./libft/ -lft -lm -o projection

#include "libSDL2/include/SDL2/SDL.h"
#include "libft/includes/libft.h"
#include "unistd.h"
#include "stdint.h"
#include "math.h"

# define WIN_W 800
# define WIN_H 600

typedef struct s_vector {
	int	x;
	int	y;
	int	z;
}		t_vector;

typedef struct s_vec {
	float	x;
	float	y;
	float	z;
	float	w;
}			t_vec;

typedef struct s_tri {
	t_vec	p[3];
}			t_tri;

typedef struct s_pixel {
	uint32_t	x;
	uint32_t	y;
}				t_pixel;

typedef struct s_img {
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_img;
typedef t_img	t_buffer;

typedef struct s_mat4 {
	float m[4][4];
}			t_mat4;

typedef struct s_rend
{
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	void			*win_pixels;
	t_buffer		*win_buffer;
	int				win_pixel_pitch;
	t_bool			run;
}					t_rend;

typedef struct s_doom {
	t_rend		rend;
	t_tri		*cube;
	t_mat4		m_proj;
	t_vec		camera;
	int			tricount;
	float		x_rot;
	float		z_rot;
	float		y_rot;
	float		distance;
	int			cam_fov;
}				t_doom;

void	drawtriangle(t_buffer *buf, t_vector v1, t_vector v2, t_vector v3);

//	MATH
/******************************************************************************/

float	vector_dot_product(t_vec va, t_vec vb)
{
	return (va.x * vb.x + va.y * vb.y + va.z * vb.z);
}

t_vec	vector_cross_product(t_vec va, t_vec vb)
{
	t_vec	result;

	result.x = va.y * vb.z - va.z * vb.y;
	result.y = va.z * vb.x - va.x * vb.z;
	result.z = va.x * vb.y - va.y * vb.x;
	return (result);
}

/*
*	Matrix multiply vector [i] with [m], applying the result into vector [o].
*/
t_vec	matrix_multiplyvector(t_vec i, t_mat4 m)
{
	t_vec	ret;

	ret.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] \
	+ i.w * m.m[3][0];
	ret.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] \
	+ i.w * m.m[3][1];
	ret.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] \
	+ i.w * m.m[3][2];
	ret.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] \
	+ i.w * m.m[3][3];
	return (ret);
}

t_mat4	matrix_init_unitmatrix(void)
{
	t_mat4 matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

t_mat4 matrix_init_x_rotationmatrix(float rad_angle)
{
	t_mat4	matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(rad_angle);
	matrix.m[1][2] = sinf(rad_angle);
	matrix.m[2][1] = -sinf(rad_angle);
	matrix.m[2][2] = cosf(rad_angle);
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

t_mat4 matrix_init_y_rotationmatrix(float rad_angle)
{
	t_mat4	matrix;
	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = cosf(rad_angle);
	matrix.m[0][2] = sinf(rad_angle);
	matrix.m[2][0] = -sinf(rad_angle);
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = cosf(rad_angle);
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

t_mat4 matrix_init_z_rotationmatrix(float rad_angle)
{
	t_mat4	matrix;
	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = cosf(rad_angle);
	matrix.m[0][1] = sinf(rad_angle);
	matrix.m[1][0] = -sinf(rad_angle);
	matrix.m[1][1] = cosf(rad_angle);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

t_mat4 matrix_init_translation(float x, float y, float z)
{
	t_mat4	matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	matrix.m[3][0] = x;
	matrix.m[3][1] = y;
	matrix.m[3][2] = z;
	return (matrix);
}

/*
*	Initializes projection matrix for a 3d camera projection.
*	[fov] is camera field of vision in degrees,
*	[ar] is the projection's aspect ratio and
*	near/far are the clipping dimensions of the projection camera.
*/
t_mat4	matrix_init_projectionmatrix(float fov, float ar, float near, float far)
{
	t_mat4	matrix;
	float	fov_rad;
	
	fov_rad = 1.0f / tanf(fov * 0.5f / 180.f * M_PI);

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = ar * fov_rad;
	matrix.m[1][1] = fov_rad;
	matrix.m[2][2] = far / (far - near);
	matrix.m[3][2] = (-far * near) / (far - near);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][3] = 0.0f;
	return (matrix);
}

/*
*	Combining two matrices means that each cell equals the sum of rows
*	multiplied by columns.
*/
t_mat4	matrix_multiplymatrix(t_mat4 m1, t_mat4 m2)
{
	t_mat4	matrix;
	int		column;
	int		row;

	column = 0;
	while (column < 4)
	{
		row = 0;
		while (row < 4)
		{
			matrix.m[row][column] = \
			m1.m[row][0] * m2.m[0][column] + \
			m1.m[row][1] * m2.m[1][column] + \
			m1.m[row][2] * m2.m[2][column] + \
			m1.m[row][3] * m2.m[3][column];
			row++;
		}
		column++;
	}
	return (matrix);
}

t_vec	vector_add(t_vec v1, t_vec v2)
{
	t_vec ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_vec	vector_sub(t_vec v1, t_vec v2)
{
	t_vec ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_vec	vector_mul(t_vec v, float multiplier)
{
	t_vec ret;

	ret.x = v.x * multiplier;
	ret.y = v.y * multiplier;
	ret.z = v.z * multiplier;
	return (ret);
}

t_vec	vector_div(t_vec v, float divisor)
{
	t_vec ret;

	ret.x = v.x / divisor;
	ret.y = v.y / divisor;
	ret.z = v.z / divisor;
	return (ret);
}

float	vector_length(t_vec v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	vector_normalize(t_vec v)
{
	t_vec	ret;
	float	l;

	l = vector_length(v);
	ret.x = v.x / l;
	ret.y = v.y / l;
	ret.z = v.z / l;
	return (ret);
}


//	PROGRAM LOGIC
/******************************************************************************/

static void	init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_getout(SDL_GetError());
	doom->rend.win = SDL_CreateWindow("projtesting", SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (!doom->rend.win)
		ft_getout(SDL_GetError());
	doom->rend.renderer = SDL_CreateRenderer(doom->rend.win, -1, \
		SDL_RENDERER_ACCELERATED);
	if (!doom->rend.renderer)
		ft_getout(SDL_GetError());
	doom->rend.win_tex = SDL_CreateTexture(doom->rend.renderer, \
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!doom->rend.win_tex)
		ft_getout(SDL_GetError());
	doom->rend.run = TRUE;
	//
	doom->tricount = 12;
	doom->x_rot = 0;
	doom->z_rot = 0;
	doom->camera = (t_vec){0, 0, 0, 1};
	doom->cam_fov = 90;
	doom->cube = (t_tri *)malloc(sizeof(t_tri) * doom->tricount);
	if (!doom->cube)
		ft_getout("failed to malloc cube!");
	//south
	doom->cube[0].p[0] = (t_vec){0.0f, 0.0f, 0.0f, 1};
	doom->cube[0].p[1] = (t_vec){0.0f, 1.0f, 0.0f, 1};
	doom->cube[0].p[2] = (t_vec){1.0f, 1.0f, 0.0f, 1};
	doom->cube[1].p[0] = (t_vec){0.0f, 0.0f, 0.0f, 1};
	doom->cube[1].p[1] = (t_vec){1.0f, 1.0f, 0.0f, 1};
	doom->cube[1].p[2] = (t_vec){1.0f, 0.0f, 0.0f, 1};
	//east
	doom->cube[2].p[0] = (t_vec){1.0f, 0.0f, 0.0f, 1};
	doom->cube[2].p[1] = (t_vec){1.0f, 1.0f, 0.0f, 1};
	doom->cube[2].p[2] = (t_vec){1.0f, 1.0f, 1.0f, 1};
	doom->cube[3].p[0] = (t_vec){1.0f, 0.0f, 0.0f, 1};
	doom->cube[3].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1};
	doom->cube[3].p[2] = (t_vec){1.0f, 0.0f, 1.0f, 1};
	//north
	doom->cube[4].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1};
	doom->cube[4].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1};
	doom->cube[4].p[2] = (t_vec){0.0f, 1.0f, 1.0f, 1};
	doom->cube[5].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1};
	doom->cube[5].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1};
	doom->cube[5].p[2] = (t_vec){0.0f, 0.0f, 1.0f, 1};
	//west
	doom->cube[6].p[0] = (t_vec){0.0f, 0.0f, 1.0f, 1};
	doom->cube[6].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1};
	doom->cube[6].p[2] = (t_vec){0.0f, 1.0f, 0.0f, 1};
	doom->cube[7].p[0] = (t_vec){0.0f, 0.0f, 1.0f, 1};
	doom->cube[7].p[1] = (t_vec){0.0f, 1.0f, 0.0f, 1};
	doom->cube[7].p[2] = (t_vec){0.0f, 0.0f, 0.0f, 1};
	//top
	doom->cube[8].p[0] = (t_vec){0.0f, 1.0f, 0.0f, 1};
	doom->cube[8].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1};
	doom->cube[8].p[2] = (t_vec){1.0f, 1.0f, 1.0f, 1};
	doom->cube[9].p[0] = (t_vec){0.0f, 1.0f, 0.0f, 1};
	doom->cube[9].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1};
	doom->cube[9].p[2] = (t_vec){1.0f, 1.0f, 0.0f, 1};
	//bottom
	doom->cube[10].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1};
	doom->cube[10].p[1] = (t_vec){0.0f, 0.0f, 1.0f, 1};
	doom->cube[10].p[2] = (t_vec){0.0f, 0.0f, 0.0f, 1};
	doom->cube[11].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1};
	doom->cube[11].p[1] = (t_vec){0.0f, 0.0f, 0.0f, 1};
	doom->cube[11].p[2] = (t_vec){1.0f, 0.0f, 0.0f, 1};

	doom->distance = 16;

	doom->m_proj = matrix_init_projectionmatrix(doom->cam_fov, \
	(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);

}

static void	cleanup(t_doom *doom)
{
	SDL_DestroyTexture(doom->rend.win_tex);
	SDL_DestroyRenderer(doom->rend.renderer);
	SDL_DestroyWindow(doom->rend.win);
	free(doom->rend.win_buffer->px);
	free(doom->rend.win_buffer);
	SDL_Quit();
}

static void	keyevent(t_doom *doom, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->window.event == SDL_WINDOWEVENT_CLOSE)
			doom->rend.run = FALSE;
		if (e->key.keysym.sym == SDLK_q && doom->cam_fov > 1)
		{
			doom->cam_fov--;
			doom->m_proj = matrix_init_projectionmatrix(doom->cam_fov, \
			(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
		}
		if (e->key.keysym.sym == SDLK_e && doom->cam_fov < 180)
		{
			doom->cam_fov++;
			doom->m_proj = matrix_init_projectionmatrix(doom->cam_fov, \
			(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
		}
		if (e->key.keysym.sym == SDLK_UP)
		{
			doom->distance += 0.1f;
		}
		if (e->key.keysym.sym == SDLK_DOWN && doom->distance > 1.0f)
		{
			doom->distance -= 0.1f;
		}
	}
}

static void	drawlogic (t_doom *doom)
{
	t_tri	tri_projected;
	t_tri	tri_transformed;

	t_mat4	mrot_z;
	t_mat4	mrot_x;
	mrot_x = matrix_init_x_rotationmatrix(doom->x_rot * 0.5);
	mrot_z = matrix_init_z_rotationmatrix(doom->z_rot * 0.25);

	t_mat4 	mat_translation;
	t_mat4	mat_world;
	mat_translation = matrix_init_translation(0.0f, 0.0f, doom->distance);
	//world space rotation, then translation
	mat_world = matrix_init_unitmatrix();
	mat_world = matrix_multiplymatrix(mrot_z, mrot_x);
	mat_world = matrix_multiplymatrix(mat_world, mat_translation);

	for (int i = 0; i < doom->tricount; i++)
	{
		//multiply each triangle with the world matrix (all transformations combined)
		tri_transformed.p[0] = matrix_multiplyvector(doom->cube[i].p[0], mat_world);
		tri_transformed.p[1] = matrix_multiplyvector(doom->cube[i].p[1], mat_world);
		tri_transformed.p[2] = matrix_multiplyvector(doom->cube[i].p[2], mat_world);

		//calculate triangle normal with the crossproduct of the first and last
		//lines that make up the triangle. Also the normal is normalized.
		t_vec	normal;
		t_vec	line1;
		t_vec	line2;
		//get both lines from the first point on the triangle
		line1 = vector_sub(tri_transformed.p[1], tri_transformed.p[0]);
		line2 = vector_sub(tri_transformed.p[2], tri_transformed.p[0]);
		//crossproduct to find normal
		normal = vector_normalize(vector_cross_product(line1, line2));
		//i honestly dont know why we normalize the normalized normal at this point lmao
		float	normal_len;
		normal_len = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal.x /= normal_len;
		normal.y /= normal_len;
		normal.z /= normal_len;

		//if (normal.z < 0) //negative z-value for normal means that the triangle is facing the camera!
		if (vector_dot_product(normal, tri_transformed.p[0]) < 0) //negative dot-product is a more accurate way of solving the above.
		{	//if our camera would move, dot_product's second argument should be (tri_trans.p[0] - cameravector)
			//project to 2D view
			tri_projected.p[0] = matrix_multiplyvector(tri_transformed.p[0], doom->m_proj);
			tri_projected.p[1] = matrix_multiplyvector(tri_transformed.p[1], doom->m_proj);
			tri_projected.p[2] = matrix_multiplyvector(tri_transformed.p[2], doom->m_proj);
			//to scale projected coordinates into view, we need to normalize it
			tri_projected.p[0] = vector_div(tri_projected.p[0], tri_projected.p[0].w);
			tri_projected.p[1] = vector_div(tri_projected.p[1], tri_projected.p[1].w);
			tri_projected.p[2] = vector_div(tri_projected.p[2], tri_projected.p[2].w);
			//offset into visible screen space
			t_vec	viewoffset = (t_vec){1.0f, 1.0f, 0, 1};
			tri_projected.p[0] = vector_add(tri_projected.p[0], viewoffset);
			tri_projected.p[1] = vector_add(tri_projected.p[1], viewoffset);
			tri_projected.p[2] = vector_add(tri_projected.p[2], viewoffset);
			tri_projected.p[0].x *= 0.5f * (float)WIN_W;
			tri_projected.p[0].y *= 0.5f * (float)WIN_H;
			tri_projected.p[1].x *= 0.5f * (float)WIN_W;
			tri_projected.p[1].y *= 0.5f * (float)WIN_H;
			tri_projected.p[2].x *= 0.5f * (float)WIN_W;
			tri_projected.p[2].y *= 0.5f * (float)WIN_H;
			drawtriangle(doom->rend.win_buffer, \
			(t_vector){tri_projected.p[0].x, tri_projected.p[0].y, 0},
			(t_vector){tri_projected.p[1].x, tri_projected.p[1].y, 0},
			(t_vector){tri_projected.p[2].x, tri_projected.p[2].y, 0});
		}
	}
}

static void	loop(t_doom	*doom)
{
	SDL_Event	e;

	doom->x_rot += 0.001;
	doom->z_rot += 0.001;

	ft_bzero(doom->rend.win_buffer->px, WIN_H * WIN_W * sizeof(uint32_t));
	drawlogic(doom);
	keyevent(doom, &e);
	if (SDL_LockTexture(doom->rend.win_tex, NULL, \
		&doom->rend.win_pixels, &doom->rend.win_pixel_pitch) < 0)
		ft_getout(SDL_GetError());
	ft_memcpy(doom->rend.win_pixels, doom->rend.win_buffer->px, \
	WIN_H * doom->rend.win_pixel_pitch);
	SDL_UnlockTexture(doom->rend.win_tex);
	if (SDL_RenderCopy(doom->rend.renderer, doom->rend.win_tex, NULL, NULL) < 0)
		ft_getout(SDL_GetError());
	SDL_RenderPresent(doom->rend.renderer);
}

int	main(void)
{
	t_doom		doom;

	ft_bzero(&doom.rend, sizeof(t_rend));
	doom.rend.win_buffer = (t_buffer *)malloc(sizeof(t_buffer));
	if (!doom.rend.win_buffer)
		ft_getout("failed to initialize main buffer");
	doom.rend.win_buffer->w = WIN_W;
	doom.rend.win_buffer->h = WIN_H;
	doom.rend.win_buffer->px = ft_memalloc(sizeof(uint32_t) * WIN_H * WIN_W);
	init(&doom);
	while (doom.rend.run)
		loop(&doom);
	cleanup(&doom);
	return (0);
}
