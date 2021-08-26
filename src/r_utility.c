#include "doom.h"

/*
*	Returns modified [value] by scaling it into the range of
*	[output.start] to [output.end] from its original input range.
*	Invalid cases where value is outside given range or if
*	(input.end - input.start == 0), function returns (0).
*/
long	map_value_to_range(t_range input, t_range output, long value)
{
	float	map_unit;

	if (input.end - input.start == 0)
		return (0);
	if (value > input.end || value < input.start)
		return (0);
	map_unit = (output.end - output.start) / (input.end - input.start);
	return (output.start + (long)(map_unit * (value - input.start)));
}

/*
*	Map signed values into unsigned buffer which x/y limit should be given as
*	[limit].
*/
uint32_t	map_value_to_buffer(t_range input, uint32_t limit, long value)
{
	float	map_unit;

	if (input.end - input.start == 0)
		return (0);
	if (value > input.end || value < input.start)
		return (0);
	map_unit = (limit / (input.end - input.start));
	return ((uint32_t)(map_unit * (value - input.start)));
}
