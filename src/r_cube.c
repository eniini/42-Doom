#include "doom.h"

static void	drawtriangle(t_buffer *buf, t_ivec3 v1, t_ivec3 v2, t_ivec3 v3)
{
	draw_vector_line(buf, (t_line){v1, v2, 0}, 0xffa6a6a6);
	draw_vector_line(buf, (t_line){v2, v3, 0}, 0xff848484);
	draw_vector_line(buf, (t_line){v3, v1, 0}, 0xff4f4f4f);
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

	for (int i = 0; i < doom->world.tricount; i++)
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

		//if (normal.z < 0) //negative z-value for normal means that the triangle is facing the camera!
		if (mv_dot_product(normal, tri_transformed.p[0]) < 0) //negative dot-product is a more accurate way of solving the above.
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
			drawtriangle(doom->rend.win_buffer, \
			(t_ivec3){(int)tri_projected.p[0].x, (int)tri_projected.p[0].y, 0},
			(t_ivec3){(int)tri_projected.p[1].x, (int)tri_projected.p[1].y, 0},
			(t_ivec3){(int)tri_projected.p[2].x, (int)tri_projected.p[2].y, 0});
		}
	}
}
