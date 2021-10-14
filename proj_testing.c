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

typedef struct s_vec3 {
	float	x;
	float	y;
	float	z;
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
	int			tricount;
	float		x_rot;
	float		z_rot;
	float		y_rot;
}				t_doom;

void	drawtriangle(t_buffer *buf, t_vector v1, t_vector v2, t_vector v3);


static void	mul_matrixvector(t_vec i, t_vec *o, t_mat4 m)
{
	float w;

	o->x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o->y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o->z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
	if (w != 0.0f)
	{
		o->x /= w;
		o->y /= w;
		o->z /= w;
	}
}

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
	doom->cube = (t_tri *)malloc(sizeof(t_tri) * doom->tricount);
	if (!doom->cube)
		ft_getout("failed to malloc cube!");
	//south
	doom->cube[0].p[0] = (t_vec){0.0f, 0.0f, 0.0f};
	doom->cube[0].p[1] = (t_vec){0.0f, 1.0f, 0.0f};
	doom->cube[0].p[2] = (t_vec){1.0f, 1.0f, 0.0f};
	doom->cube[1].p[0] = (t_vec){0.0f, 0.0f, 0.0f};
	doom->cube[1].p[1] = (t_vec){1.0f, 1.0f, 0.0f};
	doom->cube[1].p[2] = (t_vec){1.0f, 0.0f, 0.0f};
	//east
	doom->cube[2].p[0] = (t_vec){1.0f, 0.0f, 0.0f};
	doom->cube[2].p[1] = (t_vec){1.0f, 1.0f, 0.0f};
	doom->cube[2].p[2] = (t_vec){1.0f, 1.0f, 1.0f};
	doom->cube[3].p[0] = (t_vec){1.0f, 0.0f, 0.0f};
	doom->cube[3].p[1] = (t_vec){1.0f, 1.0f, 1.0f};
	doom->cube[3].p[2] = (t_vec){1.0f, 0.0f, 1.0f};
	//north
	doom->cube[4].p[0] = (t_vec){1.0f, 0.0f, 1.0f};
	doom->cube[4].p[1] = (t_vec){1.0f, 1.0f, 1.0f};
	doom->cube[4].p[2] = (t_vec){0.0f, 1.0f, 1.0f};
	doom->cube[5].p[0] = (t_vec){1.0f, 0.0f, 1.0f};
	doom->cube[5].p[1] = (t_vec){0.0f, 1.0f, 1.0f};
	doom->cube[5].p[2] = (t_vec){0.0f, 0.0f, 1.0f};
	//west
	doom->cube[6].p[0] = (t_vec){0.0f, 0.0f, 1.0f};
	doom->cube[6].p[1] = (t_vec){0.0f, 1.0f, 1.0f};
	doom->cube[6].p[2] = (t_vec){0.0f, 1.0f, 0.0f};
	doom->cube[7].p[0] = (t_vec){0.0f, 0.0f, 1.0f};
	doom->cube[7].p[1] = (t_vec){0.0f, 1.0f, 0.0f};
	doom->cube[7].p[2] = (t_vec){0.0f, 0.0f, 0.0f};
	//top
	doom->cube[8].p[0] = (t_vec){0.0f, 1.0f, 0.0f};
	doom->cube[8].p[1] = (t_vec){0.0f, 1.0f, 1.0f};
	doom->cube[8].p[2] = (t_vec){1.0f, 1.0f, 1.0f};
	doom->cube[9].p[0] = (t_vec){0.0f, 1.0f, 0.0f};
	doom->cube[9].p[1] = (t_vec){1.0f, 1.0f, 1.0f};
	doom->cube[9].p[2] = (t_vec){1.0f, 1.0f, 0.0f};
	//bottom
	doom->cube[10].p[0] = (t_vec){1.0f, 0.0f, 1.0f};
	doom->cube[10].p[1] = (t_vec){0.0f, 0.0f, 1.0f};
	doom->cube[10].p[2] = (t_vec){0.0f, 0.0f, 0.0f};
	doom->cube[11].p[0] = (t_vec){1.0f, 0.0f, 1.0f};
	doom->cube[11].p[1] = (t_vec){0.0f, 0.0f, 0.0f};
	doom->cube[11].p[2] = (t_vec){1.0f, 0.0f, 0.0f};

	//projection matrix
	float fnear = 0.1f;
	float ffar = 1000.f;
	float ffov = 90.f;
	float fratio = (float)WIN_H / (float)WIN_W;
	float ffov_rad = 1.0f / tanf(ffov * 0.5f / 180.f * M_PI);

	ft_bzero(&doom->m_proj, sizeof(t_mat4));
	doom->m_proj.m[0][0] = fratio * ffov_rad;
	doom->m_proj.m[1][1] = ffov_rad;
	doom->m_proj.m[2][2] = ffar / (ffar - fnear);
	doom->m_proj.m[3][2] = (-ffar * fnear) / (ffar - fnear);
	doom->m_proj.m[2][3] = 1.0f;
	doom->m_proj.m[3][3] = 0.0f;
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
		if (e->key.keysym.sym == SDLK_y)
		{
			doom->y_rot += 0.01;
		}
	}
}

static void	drawlogic (t_doom *doom)
{
	t_tri	tri_proj;
	t_tri	tri_trans;
	t_tri	tri_zrot;
	t_tri	tri_zxrot;
	t_tri	tri_zxyrot;
	t_mat4	mrot_z;
	t_mat4	mrot_x;
	t_mat4	mrot_y;

	ft_bzero(&mrot_z, sizeof(t_mat4));
	mrot_z.m[0][0] = cosf(doom->z_rot);
	mrot_z.m[0][1] = sinf(doom->z_rot);
	mrot_z.m[1][0] = -sinf(doom->z_rot);
	mrot_z.m[1][1] = cosf(doom->z_rot);
	mrot_z.m[2][2] = 1;
	mrot_z.m[3][3] = 1;
	ft_bzero(&mrot_x, sizeof(t_mat4));
	mrot_x.m[0][0] = 1;
	mrot_x.m[1][1] = cosf(doom->x_rot * 0.5f);
	mrot_x.m[1][2] = sinf(doom->x_rot * 0.5f);
	mrot_x.m[2][1] = -sinf(doom->x_rot * 0.5f);
	mrot_x.m[2][2] = cosf(doom->x_rot * 0.5f);
	mrot_x.m[3][3] = 1;
	ft_bzero(&mrot_y, sizeof(t_mat4));
	mrot_y.m[0][0] = 1;
	mrot_y.m[1][1] = cosf(doom->y_rot * 0.25f);
	mrot_y.m[1][2] = sinf(doom->y_rot * 0.25f);
	mrot_y.m[2][1] = -sinf(doom->y_rot * 0.25f);
	mrot_y.m[2][2] = cosf(doom->y_rot * 0.25f);
	mrot_y.m[3][3] = 1;

	for (int i = 0; i < doom->tricount; i++)
	{
		//rotate in z and then x axis
		mul_matrixvector(doom->cube[i].p[0], &tri_zrot.p[0], mrot_z);
		mul_matrixvector(doom->cube[i].p[1], &tri_zrot.p[1], mrot_z);
		mul_matrixvector(doom->cube[i].p[2], &tri_zrot.p[2], mrot_z);
		mul_matrixvector(tri_zrot.p[0], &tri_zxrot.p[0], mrot_x);
		mul_matrixvector(tri_zrot.p[1], &tri_zxrot.p[1], mrot_x);
		mul_matrixvector(tri_zrot.p[2], &tri_zxrot.p[2], mrot_x);
		mul_matrixvector(tri_zxrot.p[0], &tri_zxyrot.p[0], mrot_y);
		mul_matrixvector(tri_zxrot.p[1], &tri_zxyrot.p[1], mrot_y);
		mul_matrixvector(tri_zxrot.p[2], &tri_zxyrot.p[2], mrot_y);
		//offset to screen
		tri_trans = tri_zxyrot;
		tri_trans.p[0].z = tri_zxyrot.p[0].z + 3.0f;
		tri_trans.p[1].z = tri_zxyrot.p[1].z + 3.0f;
		tri_trans.p[2].z = tri_zxyrot.p[2].z + 3.0f;
		//project to 2D view
		mul_matrixvector(tri_trans.p[0], &tri_proj.p[0], doom->m_proj);
		mul_matrixvector(tri_trans.p[1], &tri_proj.p[1], doom->m_proj);
		mul_matrixvector(tri_trans.p[2], &tri_proj.p[2], doom->m_proj);
		//scale into view
		tri_proj.p[0].x += 1.0f;
		tri_proj.p[0].y += 1.0f;
		tri_proj.p[1].x += 1.0f;
		tri_proj.p[1].y += 1.0f;
		tri_proj.p[2].x += 1.0f;
		tri_proj.p[2].y += 1.0f;
		tri_proj.p[0].x *= 0.5f * (float)WIN_W;
		tri_proj.p[0].y *= 0.5f * (float)WIN_H;
		tri_proj.p[1].x *= 0.5f * (float)WIN_W;
		tri_proj.p[1].y *= 0.5f * (float)WIN_H;
		tri_proj.p[2].x *= 0.5f * (float)WIN_W;
		tri_proj.p[2].y *= 0.5f * (float)WIN_H;
		drawtriangle(doom->rend.win_buffer, \
		(t_vector){tri_proj.p[0].x, tri_proj.p[0].y, 0},
		(t_vector){tri_proj.p[1].x, tri_proj.p[1].y, 0},
		(t_vector){tri_proj.p[2].x, tri_proj.p[2].y, 0});
	}
}

static void	loop(t_doom	*doom)
{
	SDL_Event	e;

	doom->x_rot += 0.01;
	doom->z_rot += 0.01;

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
