#ifndef VECTOR_H
# define VECTOR_H

//used for integer-space calculations

t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
t_vector	vector_mul(t_vector v1, float mul);
t_vector	vector_div(t_vector v1, float div);

//used for floating-point calcs

float		vector2_dist(t_vector v1, t_vector v2);
t_vector	vector2_normalize(t_vector v);

#endif
