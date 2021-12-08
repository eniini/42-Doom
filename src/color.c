#include "doom.h"

/*
*	Internally consistent color interpolation, where output
*	is fully opaque (0xFFRRGGBB).
*	[p] is expected to be within the range of [0.0-1.0].
*/
uint32_t	color_lerp(uint32_t c1, uint32_t c2, double p)
{
	int	r;
	int	g;
	int	b;

	if (c1 == c2)
		return (c1);
	if (p < 0.0)
		p = 0.0;
	if (p > 1.0)
		p = 1.0;
	r = ft_i_lerp((c1 >> 16) & 255, (c2 >> 16) & 255, p);
	g = ft_i_lerp((c1 >> 8) & 255, (c2 >> 8) & 255, p);
	b = ft_i_lerp(c1 & 255, c2 & 255, p);
	return (255 << 24 | r << 16 | g << 8 | b);
}
