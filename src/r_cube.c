#include "doom.h"

/*
*	Both of these flat fills work due to both sides of the triangle having
*	equal y length. Slopes from top or bottom are calculated independently
*	and added to two points 'walking' along the both lateral sides of the shape.
*/

static void fill_botflat_tri(t_buffer *buf, t_ivec3 v1, t_ivec3 v2, t_ivec3 v3)
{
	float	slope1;
	float	slope2;
	float	curx1;
	float	curx2;
	int		scanline_y;

	slope1 = (v2.x - v1.x) / (float)(v2.y - v1.y);
	slope2 = (v3.x - v1.x) / (float)(v3.y - v1.y);
	curx1 = v1.x;
	curx2 = v1.x;
	scanline_y = v1.y;
	while (scanline_y <= v2.y)
	{
		draw_line(buf, (t_pixel){(int)curx1, scanline_y}, \
			(t_pixel){(int)curx2, scanline_y}, v1.z);
		curx1 += slope1;
		curx2 += slope2;
		scanline_y++;
	}
}

static void fill_topflat_tri(t_buffer *buf, t_ivec3 v1, t_ivec3 v2, t_ivec3 v3)
{
	float	slope1;
	float	slope2;
	float	curx1;
	float	curx2;
	int		scanline_y;
	
	slope1 = (v3.x - v1.x) / (float)(v3.y - v1.y);
	slope2 = (v3.x - v2.x) / (float)(v3.y - v2.y);
	curx1 = v3.x;
	curx2 = v3.x;
	scanline_y = v3.y;
	while (scanline_y > v1.y)
	{
		draw_line(buf, (t_pixel){(int)curx1, scanline_y}, \
			(t_pixel){(int)curx2, scanline_y}, v1.z);
		curx1 -= slope1;
		curx2 -= slope2;
		scanline_y--;
	}
}

/*	1. Sort vectors in order so that v1.y <= v2.y <= v3.y
*	2. check if two points y values are the same i.e we have a 'flat' triangle
*	3. if its not a flat, do intercept triangulation to find a midpoint on the
*	same level as the middle point (y-direction wise) to create a fourth point
*	that we can use to draw a pair of flat triangles. Link for algo:
*	sunshine2k.de/coding/java/TriangleRasterization/generalTriangle.png
*/
static void	draw_filled_tri(t_buffer *buf, t_ivec3 v1, t_ivec3 v2, t_ivec3 v3)
{
	t_ivec3	v4;

	if (v2.y < v1.y)
		ft_swap(&v1, &v2, sizeof(t_ivec3));
	if (v3.y < v1.y)
		ft_swap(&v3, &v1, sizeof(t_ivec3));
	if (v3.y < v2.y)
		ft_swap(&v3, &v2, sizeof(t_ivec3));
	if (v2.y == v3.y)
		fill_botflat_tri(buf, v1, v2, v3);
	else if (v1.y == v2.y)
		fill_topflat_tri(buf, v1, v2, v3);
	else
	{
		v4 = (t_ivec3){(int)(v1.x + (float)(v2.y - v1.y) / (float)(v3.y - v1.y) * (v3.x - v1.x)), \
		v2.y, v1.z}; //transmitting the vertex color as z value
		fill_botflat_tri(buf, v1, v2, v4);
		fill_topflat_tri(buf, v2, v4, v3);
	}
}

/*tcvec_3 is ivec + individual color OR ninja verts 2d color in as the z value !! !! !!
static void	draw_col_tri(t_buffer *buf, t_cvec3 v1, t_cvec3 v2, t_cvec3 v3)
{

}*/

static void	drawtriangle(t_buffer *buf, t_ivec3 v1, t_ivec3 v2, t_ivec3 v3)
{
	//draw_vector_line(buf, (t_line){v1, v2, 0}, 0xffa6a6a6);
	//draw_vector_line(buf, (t_line){v2, v3, 0}, 0xff848484);
	//draw_vector_line(buf, (t_line){v3, v1, 0}, 0xff4f4f4f);
	draw_filled_tri(buf, v1, v2, v3);
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

			//dumb color sampler for cube faces. FIX FT_COLOR_LERP TO USE UINT OR CREATE NEW ONE !
			int color;
			if (i < 2)
				color = 0x4caf69;
			else if (i < 4)
				color = 0x4caf9b;
			else if (i < 6)
				color = 0x4c92af;
			else if (i < 8)
				color = 0x4c61af;
			else if (i < 10)
				color = 0x694caf;
			else
				color = 0x9b4caf;
			drawtriangle(doom->rend.win_buffer, \
			(t_ivec3){(int)tri_projected.p[0].x, (int)tri_projected.p[0].y, 0xFF000000 + ft_color_lerp(0, color, fabs(dotproduct))},
			(t_ivec3){(int)tri_projected.p[1].x, (int)tri_projected.p[1].y, 0xFF000000 + ft_color_lerp(0, color, fabs(dotproduct))},
			(t_ivec3){(int)tri_projected.p[2].x, (int)tri_projected.p[2].y, 0xFF000000 + ft_color_lerp(0, color, fabs(dotproduct))});
		}
		i++;
	}
}
