#include "doom.h"

/*
*	Both of these flat fills work due to both sides of the triangle having
*	equal y length. Slopes from top or bottom are calculated independently
*	and added to two points 'walking' along the both lateral sides of the shape.
*/

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
}

static void fill_tflat_tri(t_buffer *buf, t_point p1, t_point p2, t_point p3)
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
static void check_order(t_point *p1, t_point *p2, t_point *p3)
{
	if (p2->y < p1->y)
		ft_swap(p2, p1, sizeof(t_point));
	if (p3->y < p1->y)
		ft_swap(p3, p1, sizeof(t_point));
	if (p3->y < p2->y)
		ft_swap(p3, p2, sizeof(t_point));
}

/*
*	2. check if two points y values are the same i.e we have a 'flat' triangle
*	3. if its not a flat, do intercept triangulation to find a midpoint on the
*	same level as the middle point (y-direction wise) to create a fourth point
*	that we can use to draw a pair of flat triangles. Link for algo:
*	sunshine2k.de/coding/java/TriangleRasterization/generalTriangle.png
*/
static void	draw_filled_tri(t_buffer *buf, t_point p1, t_point p2, t_point p3)
{
	t_point	p4;

	check_order(&p1, &p2, &p3);
	if (p2.y == p3.y)
		fill_bflat_tri(buf, p1, p2, p3);
	else if (p1.y == p2.y)
		fill_tflat_tri(buf, p1, p2, p3);
	else
	{
		p4 = (t_point){(int)(p1.x + (float)(p2.y - p1.y) / \
		(float)(p3.y - p1.y) * (p3.x - p1.x)), p2.y, (color_lerp(p1.c, p3.c, ft_inverse_i_lerp(p1.y, p3.y, p2.y)))};
		fill_bflat_tri(buf, p1, p2, p4);
		fill_tflat_tri(buf, p2, p4, p3);
	}
}

static void blin_bflat_tri(t_buffer *buf, t_point p1, t_point p2, t_point p3)
{
	float		slope_left;
	float		slope_right;
	float		current_left_x;
	float		current_right_x;
	int			scanline_y;
	uint32_t	left_color;
	uint32_t	right_color;
	float		p;

	slope_left = (p2.x - p1.x) / (float)(p2.y - p1.y);
	slope_right = (p3.x - p1.x) / (float)(p3.y - p1.y);
	current_left_x = p1.x;
	current_right_x = p1.x;
	scanline_y = p1.y;
	while (scanline_y <= p2.y)
	{
		p = ft_inverse_i_lerp(p1.y, p2.y, scanline_y);
		left_color = color_lerp(p1.c, p2.c, p);
		right_color = color_lerp(p1.c, p3.c, p);
		draw_line_shaded(buf, (t_pixel){(int)current_left_x, scanline_y}, \
			(t_pixel){(int)current_right_x, scanline_y}, (t_pixel){left_color, right_color});
		current_left_x += slope_left;
		current_right_x += slope_right;
		scanline_y++;
	}
}

static void blin_tflat_tri(t_buffer *buf, t_point p1, t_point p2, t_point p3)
{
	float		slope_left;
	float		slope_right;
	float		current_left_x;
	float		current_right_x;
	int			scanline_y;
	uint32_t	left_color;
	uint32_t	right_color;
	float		p;
	
	slope_left = (p3.x - p1.x) / (float)(p3.y - p1.y);
	slope_right = (p3.x - p2.x) / (float)(p3.y - p2.y);
	current_left_x = p3.x;
	current_right_x = p3.x;
	scanline_y = p3.y;
	while (scanline_y > p1.y)
	{
		p = ft_inverse_i_lerp(p1.y, p3.y, scanline_y);
		left_color = color_lerp(p1.c, p3.c, p);
		right_color = color_lerp(p2.c, p3.c, p);
		draw_line_shaded(buf, (t_pixel){(int)current_left_x, scanline_y}, \
			(t_pixel){(int)current_right_x, scanline_y}, (t_pixel){left_color, right_color});
		current_left_x -= slope_left;
		current_right_x -= slope_right;
		scanline_y--;
	}
}

static void	draw_bilinear_tri(t_buffer *buf, t_point p1, t_point p2, t_point p3)
{
	t_point		p4;
	uint32_t	col;

	check_order(&p1, &p2, &p3);
	if (p2.y == p3.y)
		blin_bflat_tri(buf, p1, p2, p3);
	if (p1.y == p2.y)
		blin_tflat_tri(buf, p1, p2, p3);
	else
	{
		col = color_lerp(p1.c, p3.c, ft_inverse_i_lerp(p1.y, p3.y, p2.y));
		p4 = (t_point){(int)(p1.x + (float)(p2.y - p1.y) \
		/ (float)(p3.y - p1.y) * (p3.x - p1.x)), p2.y, col};
		if (p4.x < p2.x)
		{
			blin_bflat_tri(buf, p1, p4, p2);
			blin_tflat_tri(buf, p4, p2, p3);
		}
			//ft_swap(&p4, &p2, sizeof(t_point));
		blin_bflat_tri(buf, p1, p2, p4);
		blin_tflat_tri(buf, p2, p4, p3);
	}
}

static void	drawtriangle(t_buffer *buf, t_point p1, t_point p2, t_point p3)
{
	//draw_vector_line(buf, (t_line){v1, v2, 0}, 0xffa6a6a6);
	//draw_vector_line(buf, (t_line){v2, v3, 0}, 0xff848484);
	//draw_vector_line(buf, (t_line){v3, v1, 0}, 0xff4f4f4f);
	draw_filled_tri(buf, p1, p2, p3);
//	draw_bilinear_tri(buf, p1, p2, p3);
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
		//if (normal.z < 0) //negative z-value for normal means that the triangle is facing the camera!
		dotproduct = mv_dot_product(normal, tri_transformed.p[0]);
		if (dotproduct < 0) //negative dot-product is a more accurate way of solving the above.
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
				color_1 = 0xff9dd8c5;
				color_2 = 0xff2b4c6b;
				color_3 = 0xffb84f80;
			}
			else if (i == 1)
			{
				color_1 = 0xff9dd8c5;
				color_2 = 0xffb84f80;
				color_3 = 0xffc08063;
			}
			else if (i == 2)
			{
				color_1 = 0xffc08063;
				color_2 = 0xffb84f80;
				color_3 = 0xff8992cf;
			}
			else if (i == 3)
			{
				color_1 = 0xffc08063;
				color_2 = 0xff8992cf;
				color_3 = 0xffc29bd7;
			}
			else if (i == 4)
			{
				color_1 = 0xffc29bd7;
				color_2 = 0xff8992cf;
				color_3 = 0xffd2cfec;
			}
			else if (i == 5)
			{
				color_1 = 0xffc29bd7;
				color_2 = 0xffd2cfec;
				color_3 = 0xff0e0a1a;
			}
			else if (i == 6)
			{
				color_1 = 0xff0e0a1a;
				color_2 = 0xffd2cfec;
				color_3 = 0xff2b4c6b;
			}
			else if (i == 7)
			{
				color_1 = 0xff0e0a1a;
				color_2 = 0xff2b4c6b;
				color_3 = 0xff9dd8c5;
			}
			else if (i == 8)
			{
				color_1 = 0xff2b4c6b;
				color_2 = 0xffd2cfec;
				color_3 = 0xff8992cf;
			}
			else if (i == 9)
			{
				color_1 = 0xff2b4c6b;
				color_2 = 0xff8992cf;
				color_3 = 0xffb84f80;
			}
			else if (i == 10)
			{
				color_1 = 0xffc29bd7;
				color_2 = 0xff0e0a1a;
				color_3 = 0xff9dd8c5;
			}
			else
			{
				color_1 = 0xffc29bd7;
				color_2 = 0xff9dd8c5;
				color_3 = 0xffc08063;
			}
			//drawtriangle(doom->rend.win_buffer, \
			//(t_ivec3){(int)tri_projected.p[0].x, (int)tri_projected.p[0].y, color_lerp(C_BLACK, color_1, fabs(dotproduct))},
			//(t_ivec3){(int)tri_projected.p[1].x, (int)tri_projected.p[1].y, color_lerp(C_BLACK, color_1, fabs(dotproduct))},
			//(t_ivec3){(int)tri_projected.p[2].x, (int)tri_projected.p[2].y, color_lerp(C_BLACK, color_1, fabs(dotproduct))});
			drawtriangle(doom->rend.win_buffer, \
			(t_point){(int)tri_projected.p[0].x, (int)tri_projected.p[0].y, color_lerp(C_BLACK, color_1, fabs(dotproduct))},
			(t_point){(int)tri_projected.p[1].x, (int)tri_projected.p[1].y, color_lerp(C_BLACK, color_2, fabs(dotproduct))},
			(t_point){(int)tri_projected.p[2].x, (int)tri_projected.p[2].y, color_lerp(C_BLACK, color_3, fabs(dotproduct))});
		}
		i++;
	}
}
