#include "doom.h"

uint32_t	get_baryentric_color(t_fpoint p, t_fpoint p0, t_fpoint p1, t_fpoint p2)
{
	float		d;
	t_fvec3		lambda;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	float den_alpha = ((p1.y - p2.y) * p0.x + (p2.x - p1.x) * p0.y + (p1.x * p2.y) - (p2.x * p1.y));
	float den_beta = ((p2.y - p0.y) * p1.x + (p0.x - p2.x) * p1.y + (p2.x * p0.y) - (p0.x * p2.y));
	float alpha = ((p1.y - p2.y) * p.x + (p2.x - p1.x) * p.y + (p1.x * p2.y) - (p2.x * p1.y)) / den_alpha;
	float beta = ((p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y + (p2.x * p0.y) - (p0.x * p2.y)) / den_beta;
	float gamma = 1.0 - alpha - beta;

	r = ((p0.c >> 16) & 255) * alpha + ((p1.c >> 16) & 255) * beta + ((p2.c >> 16) & 255) * gamma;
	g = ((p0.c >> 8) & 255) * alpha + ((p1.c >> 8) & 255) * beta + ((p2.c >> 8) & 255) * gamma;
	b = (p0.c & 255) * alpha + (p1.c & 255) * beta + (p2.c & 255) * gamma;
	return ((0xFF << 24 | r << 16 | g << 8 | b));
}

/*
*	Both of these flat fills work due to both sides of the triangle having
*	equal y length. Slopes from top or bottom are calculated independently
*	and added to two points 'walking' along the both lateral sides of the shape.
*/

/*
static void fill_bflat_tri(t_buffer *buf, t_point p1, t_point p2, t_point p3)
{
	float	slope_left;
	float	slope_right;
	float	current_left_x;
	float	current_right_x;
	int		scanline_y;

	slope_left = (p2.x - p1.x) / (float)(p2.y - p1.y);
	slope_right = (p3.x - p1.x) / (float)(p3.y - p1.y);
	current_left_x = p1.x;
	current_right_x = p1.x;
	scanline_y = p1.y;
	while (scanline_y <= p2.y)
	{
		draw_line(buf, (t_pixel){(int)current_left_x, scanline_y}, \
			(t_pixel){(int)current_right_x, scanline_y}, p1.c);
		current_left_x += slope_left;
		current_right_x += slope_right;
		scanline_y++;
	}
}*/

static void fill_tflat_tri(t_buffer *buf, t_fpoint p1, t_fpoint p2, t_fpoint p3)
{
	float	slope_left;
	float	slope_right;
	float	current_left_x;
	float	current_right_x;
	int		scanline_y;
	
	slope_left = (p3.x - p1.x) / (float)(p3.y - p1.y);
	slope_right = (p3.x - p2.x) / (float)(p3.y - p2.y);
	current_left_x = p3.x;
	current_right_x = p3.x;
	scanline_y = p3.y;
	while (scanline_y > p1.y)
	{
		draw_line(buf, (t_pixel){(int)current_left_x, scanline_y}, \
			(t_pixel){(int)current_right_x, scanline_y}, p1.c);
		current_left_x -= slope_left;
		current_right_x -= slope_right;
		scanline_y--;
	}
}


//	1. Sort vectors in order so that v1.y <= v2.y <= v3.y (v1 is topmost)
static void check_order(t_fpoint *p1, t_fpoint *p2, t_fpoint *p3)
{
	if (p2->y < p1->y)
		ft_swap(p2, p1, sizeof(t_fpoint));
	if (p3->y < p1->y)
		ft_swap(p3, p1, sizeof(t_fpoint));
	if (p3->y < p2->y)
		ft_swap(p3, p2, sizeof(t_fpoint));
}

/*
*	2. check if two points y values are the same i.e we have a 'flat' triangle
*	3. if its not a flat, do intercept triangulation to find a midpoint on the
*	same level as the middle point (y-direction wise) to create a fourth point
*	that we can use to draw a pair of flat triangles. Link for algo:
*	sunshine2k.de/coding/java/TriangleRasterization/generalTriangle.png
*/
/*
static void	draw_filled_tri(t_buffer *buf, t_point p1, t_point p2, t_point p3)
{
	t_point	p4;

	check_order(&p1, &p2, &p3);
	if (p2.y == p3.y)
		fill_bflat_tri(buf, p1, p2, p3);
	else if (p1.y == p2.y)
		fill_tflat_tri(buf, p2, p1, p3);
	else
	{
		p4 = (t_point){(int)(p1.x + (float)(p2.y - p1.y) / \
		(float)(p3.y - p1.y) * (p3.x - p1.x)), p2.y, p1.c};
		fill_bflat_tri(buf, p1, p2, p4);
		fill_tflat_tri(buf, p2, p4, p3);
	}
}*/

static void blin_bflat_tri(t_buffer *buf, t_fpoint p1, t_fpoint p2, t_fpoint p3)
{
	float		slope_left;
	float		slope_right;
	float		current_left_x;
	float		current_right_x;
	float		scanline_y;
	float		x_left;
	float		x_right;
	float		min;
	float		max;

	slope_left = (p2.x - p1.x) / (p2.y - p1.y);
	slope_right = (p3.x - p1.x) / (p3.y - p1.y);
	current_left_x = p1.x;
	current_right_x = p1.x;
	scanline_y = p1.y;
	min = p2.x;
	if (p1.x < p2.x && p1.x < p3.x)
		min = p1.x;
	max = p3.x;
	if (p1.x > p2.x && p1.x > p3.x)
		max = p1.x;
	while ((int)scanline_y <= (int)p2.y)
	{
		x_left = ft_clamp_d(current_left_x, min, max);
		x_right = ft_clamp_d(current_right_x, min, max);
		if (current_left_x <= current_right_x)
		{
			while (x_left <= x_right) //we need an int-based drawpixel lmao
				draw_pixel((uint)x_left++, (uint)scanline_y, buf, \
				get_baryentric_color((t_fpoint){x_left, scanline_y, 0}, p1, p2, p3));
		}
		else
		{
			while (x_left > x_right)
				draw_pixel((uint)x_left--, (uint)scanline_y, buf, \
				get_baryentric_color((t_fpoint){x_left, scanline_y, 0}, p1, p2, p3));
		}
		current_left_x += slope_left;
		current_right_x += slope_right;
		scanline_y++;
	}
}


static void blin_tflat_tri(t_buffer *buf, t_fpoint p1, t_fpoint p2, t_fpoint p3)
{
	float		slope_left;
	float		slope_right;
	float		current_left_x;
	float		current_right_x;
	float		scanline_y;
	float		p;
	float		x;

	slope_left = (p3.x - p1.x) / (p3.y - p1.y);
	slope_right = (p3.x - p2.x) / (p3.y - p2.y);
	current_left_x = p3.x;
	current_right_x = p3.x;
	scanline_y = p3.y;
	while ((int)scanline_y >= (int)p1.y)
	{
		if (current_left_x <= current_right_x)
		{
			x = current_left_x;
			while (x <= current_right_x && x >= p1.x)
				draw_pixel((uint)x++, (uint)scanline_y, buf, \
				get_baryentric_color((t_fpoint){x, scanline_y, 0}, p1, p2, p3));
		}
		else
		{
			x = current_right_x;
			while (x <= current_left_x && x >= p2.x)
				draw_pixel((uint)x++, (uint)scanline_y, buf, \
				get_baryentric_color((t_fpoint){x, scanline_y, 0}, p1, p2, p3));
		}
		current_left_x -= slope_left;
		current_right_x -= slope_right;
		scanline_y--;
	}
}

static void	draw_bilinear_tri(t_buffer *buf, t_fpoint p1, t_fpoint p2, t_fpoint p3)
{
	t_fpoint	p4;
	uint32_t	col;

	check_order(&p1, &p2, &p3);
	if (p2.y == p3.y)
		blin_bflat_tri(buf, p1, p2, p3);
	if (p1.y == p2.y)
		blin_tflat_tri(buf, p2, p1, p3);
	else
	{
		p4 = (t_fpoint){(p1.x + (p2.y - p1.y) / (p3.y - p1.y) * (p3.x - p1.x)), p2.y, 0};
		p4.c = get_baryentric_color(p4, p1, p2, p3);
		if (p2.x < p1.x && p2.x < p3.x) //right-leaning triangle
		{
			blin_bflat_tri(buf, p1, p2, p4);
			blin_tflat_tri(buf, p2, p4, p3);
		}
		else
		{
			blin_bflat_tri(buf, p1, p4, p2);
			blin_tflat_tri(buf, p4, p2, p3);
		}
	}
}

static void	drawtriangle(t_buffer *buf, t_fpoint p1, t_fpoint p2, t_fpoint p3)
{
	//flat
	//draw_filled_tri(buf, p1, p2, p3);
	//interpolated vertices
	draw_bilinear_tri(buf, p1, p2, p3);
	//wireframe
	draw_vector_line(buf, (t_line){(t_ivec3){p1.x, p1.y, 0}, (t_ivec3){p2.x, p2.y, 0}, 0}, C_DEBUG);
	draw_vector_line(buf, (t_line){(t_ivec3){p2.x, p2.y, 0}, (t_ivec3){p3.x, p3.y, 0}, 0}, C_DEBUG);
	draw_vector_line(buf, (t_line){(t_ivec3){p3.x, p3.y, 0}, (t_ivec3){p1.x, p1.y, 0}, 0}, C_DEBUG);
}

void	draw_cube (t_doom *doom)
{
	t_tri	tri_projected;
	t_tri	tri_transformed;

	t_mat4	mrot_z;
	t_mat4	mrot_x;
	mrot_x = mm_init_rotationmatrix_x(doom->world.cube_rotation.x * 0.5);
	mrot_z = mm_init_rotationmatrix_z(doom->world.cube_rotation.z * 0.25);

	t_mat4 	mat_translation;
	t_mat4	mat_world;
	mat_translation = mm_init_translation(0.0f, 0.0f, doom->world.cam_distance);
	//world space rotation, then translation
	mat_world = mm_init_unitmatrix();
	mat_world = mm_multiply_matrix(mrot_z, mrot_x);
	mat_world = mm_multiply_matrix(mat_world, mat_translation);

	int i = 0;
	while (i < doom->world.tricount)
	{
		//multiply each triangle with the world matrix (all transformations combined)
		tri_transformed.p[0] = mm_multiply_vector(doom->world.cube[i].p[0], mat_world);
		tri_transformed.p[1] = mm_multiply_vector(doom->world.cube[i].p[1], mat_world);
		tri_transformed.p[2] = mm_multiply_vector(doom->world.cube[i].p[2], mat_world);

		//calculate triangle normal with the crossproduct of the first and last
		//lines that make up the triangle. Also the normal is normalized.
		t_vector	normal;
		t_vector	line1;
		t_vector	line2;
		//get both lines from the first point on the triangle
		line1 = mv_substract(tri_transformed.p[1], tri_transformed.p[0]);
		line2 = mv_substract(tri_transformed.p[2], tri_transformed.p[0]);
		//crossproduct to find normal
		normal = mv_normalize(mv_cross_product(line1, line2));
		//i honestly dont know why we normalize the normalized normal at this point lmao
		float	normal_len;
		normal_len = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal.x /= normal_len;
		normal.y /= normal_len;
		normal.z /= normal_len;

		float dotproduct;
		dotproduct = mv_dot_product(normal, tri_transformed.p[0]);
		if (dotproduct < 0) //negative dot-product is a more accurate way of solving the above.
		//if (dotproduct) //TESTING ONLY
		{	//if our camera would move, dot_product's second argument should be (tri_trans.p[0] - cameravector)
			//project to 2D view
			tri_projected.p[0] = mm_multiply_vector(tri_transformed.p[0], doom->world.m_proj);
			tri_projected.p[1] = mm_multiply_vector(tri_transformed.p[1], doom->world.m_proj);
			tri_projected.p[2] = mm_multiply_vector(tri_transformed.p[2], doom->world.m_proj);
			//to scale projected coordinates into view, we need to normalize it
			tri_projected.p[0] = mv_divide(tri_projected.p[0], tri_projected.p[0].w);
			tri_projected.p[1] = mv_divide(tri_projected.p[1], tri_projected.p[1].w);
			tri_projected.p[2] = mv_divide(tri_projected.p[2], tri_projected.p[2].w);
			//offset into visible screen space
			t_vector	viewoffset = (t_vector){1.0f, 1.0f, 0, 1};
			tri_projected.p[0] = mv_add(tri_projected.p[0], viewoffset);
			tri_projected.p[1] = mv_add(tri_projected.p[1], viewoffset);
			tri_projected.p[2] = mv_add(tri_projected.p[2], viewoffset);
			tri_projected.p[0].x *= 0.5f * (float)WIN_W;
			tri_projected.p[0].y *= 0.5f * (float)WIN_H;
			tri_projected.p[1].x *= 0.5f * (float)WIN_W;
			tri_projected.p[1].y *= 0.5f * (float)WIN_H;
			tri_projected.p[2].x *= 0.5f * (float)WIN_W;
			tri_projected.p[2].y *= 0.5f * (float)WIN_H;

			//dumb color sampler for cube faces.
			uint32_t	color_1;
			uint32_t	color_2;
			uint32_t	color_3;
			if (i == 0)
			{
				color_1 = C_OCHRE;
				color_2 = C_LIME;
				color_3 = C_GRAPE;
			}
			else if (i == 1)
			{
				color_1 = C_OCHRE;
				color_2 = C_GRAPE;
				color_3 = C_LEMON;
			}
			else if (i == 2)
			{
				color_1 = C_LEMON;
				color_2 = C_GRAPE;
				color_3 = C_PLUM;
			}
			else if (i == 3)
			{
				color_1 = C_LEMON;
				color_2 = C_PLUM;
				color_3 = C_BRICK;
			}
			else if (i == 4)
			{
				color_1 = C_BRICK;
				color_2 = C_PLUM;
				color_3 = C_GRASS;
			}
			else if (i == 5)
			{
				color_1 = C_BRICK;
				color_2 = C_GRASS;
				color_3 = C_SKY;
			}
			else if (i == 6)
			{
				color_1 = C_SKY;
				color_2 = C_GRASS;
				color_3 = C_LIME;
			}
			else if (i == 7)
			{
				color_1 = C_SKY;
				color_2 = C_LIME;
				color_3 = C_OCHRE;
			}
			else if (i == 8)
			{
				color_1 = C_LIME;
				color_2 = C_GRASS;
				color_3 = C_PLUM;
			}
			else if (i == 9)
			{
				color_1 = C_LIME;
				color_2 = C_PLUM;
				color_3 = C_GRAPE;
			}
			else if (i == 10)
			{
				color_1 = C_BRICK;
				color_2 = C_SKY;
				color_3 = C_OCHRE;
			}
			else
			{
				color_1 = C_BRICK;
				color_2 = C_OCHRE;
				color_3 = C_LEMON;
			}
			/*
			drawtriangle(doom->rend.win_buffer, \
			(t_ivec3){(int)tri_projected.p[0].x, (int)tri_projected.p[0].y, color_lerp(C_BLACK, color_1, fabs(dotproduct))},
			(t_ivec3){(int)tri_projected.p[1].x, (int)tri_projected.p[1].y, color_lerp(C_BLACK, color_1, fabs(dotproduct))},
			(t_ivec3){(int)tri_projected.p[2].x, (int)tri_projected.p[2].y, color_lerp(C_BLACK, color_1, fabs(dotproduct))});*/
			/*drawtriangle(doom->rend.win_buffer,
			(t_fpoint){tri_projected.p[0].x, tri_projected.p[0].y, color_lerp(C_BLACK, color_1, fabs(dotproduct))},
			(t_fpoint){tri_projected.p[1].x, tri_projected.p[1].y, color_lerp(C_BLACK, color_2, fabs(dotproduct))},
			(t_fpoint){tri_projected.p[2].x, tri_projected.p[2].y, color_lerp(C_BLACK, color_3, fabs(dotproduct))});*/
			drawtriangle(doom->rend.win_buffer, \
			(t_fpoint){tri_projected.p[0].x, tri_projected.p[0].y, color_1},
			(t_fpoint){tri_projected.p[1].x, tri_projected.p[1].y, color_2},
			(t_fpoint){tri_projected.p[2].x, tri_projected.p[2].y, color_3});
		}
		i++;
	}
}
