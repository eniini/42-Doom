#ifndef M_UTILS_H
# define M_UTILS_H

# include "defines.h"

//vector funcs

t_vector	mv_add(t_vector va, t_vector vb);
t_vector	mv_substract(t_vector va, t_vector vb);
t_vector	mv_multiply(t_vector va, float multiplier);
t_vector	mv_divide(t_vector va, float divisor);

float		mv_length(t_vector v);
float		mv_distance_to_vector(t_vector va, t_vector vb);

t_vector	mv_normalize(t_vector v);

float		mv_dot_product(t_vector va, t_vector vb);

t_vector	mv_cross_product(t_vector va, t_vector vb);

//4x4 matrix funcs

t_vector	mm_multiply_vector(t_vector v, t_mat4 m);

t_mat4		mm_multiply_matrix(t_mat4 ma, t_mat4 mb);

t_mat4		mm_init_unitmatrix(void);

t_mat4		mm_init_rotationmatrix_x(float angle_in_rads);
t_mat4		mm_init_rotationmatrix_y(float angle_in_rads);
t_mat4		mm_init_rotationmatrix_z(float angle_in_rads);

t_mat4		mm_init_translation(float x, float y, float z);

t_mat4		mm_init_3d_projection(float fov, float ar, float near, float far);

#endif
