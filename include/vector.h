#ifndef VECTOR_H
# define VECTOR_H

t_vector2	vector2_add(t_vector2 v1, t_vector2 v2);
t_vector2	vector2_sub(t_vector2 v1, t_vector2 v2);
t_vector2	vector2_mul(t_vector2 v1, float mul);
t_vector2	vector2_div(t_vector2 v1, float div);

float		vector2_dist(t_vector2 v1, t_vector2 v2);
t_vector2	vector2_normalize(t_vector2 v);

#endif
