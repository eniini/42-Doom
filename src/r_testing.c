#include "doom.h"

/*
static void	draw_rays(t_buffer *buf, t_vector start, t_vector end, uint32_t c)
{
	int		ray_start;
	int		ray_i;
	int		wall_h;
	int		wall_len;
	t_line	ray;

	wall_len = ft_abs(end.x - start.x);
	ray_i = 0;
	if (end.x < start.x)
		ray_start = end.x;
	else
		ray_start = start.x;
	while (ray_i < wall_len)
	{
		wall_h = ft_i_lerp(start.y, end.y, ray_i / (double)wall_len);
		ray.start = (t_ivec3){(ray_start + ray_i) + WIN_HW, WIN_HH - wall_h, 0};
		ray.end = (t_ivec3){(ray_start + ray_i) + WIN_HW, WIN_HH + wall_h, 0};
		draw_vector_line(buf, ray, c);
		ray_i++;
	}
}*/

/*
static void	draw_room3d(t_buffer *buf, t_world world)
{
	int			i = 0;
	t_vector	uv_start = (t_vector){0, 0, 0, 1};
	t_vector	uv_end = (t_vector){0, 0, 0, 1};
	int distance = 100;

	int		fov = 60;
	//float	d = 1 / tan(fov / 2);

	draw_line(buf, (t_pixel){WIN_W / 2, 0}, (t_pixel){WIN_W / 2, WIN_H}, C_RED);
	while (i < world.room->wallcount)
	{
		if (world.room->proj_walls[i].start.y > 0 && world.room->proj_walls[i].end.y > 0)
		{
			//t_range xinput = (t_range){room->boundingbox[1], room->boundingbox[3]};
			//t_range yinput = (t_range){room->boundingbox[0], room->boundingbox[2]};
			//t_range xoutput = (t_range){WIN_W / 2,  WIN_W};
			//t_range youtput = (t_range){0, WIN_H};
			//uv_start.x = map_value_to_range(xinput, xoutput, room->proj_walls[i].start.x);
			//uv_start.y = map_value_to_range(yinput, youtput, room->proj_walls[i].start.y);
			//uv_end.x = map_value_to_range(xinput, xoutput, room->proj_walls[i].end.x);
			//uv_end.y = map_value_to_range(yinput, youtput, room->proj_walls[i].end.y);
			uv_start.x = (world.room->proj_walls[i].start.x * distance) / world.room->proj_walls[i].start.y;
			uv_start.y = (world.room->ceil_h * distance) / world.room->proj_walls[i].start.y;
			uv_end.x = (world.room->proj_walls[i].end.x * distance) / world.room->proj_walls[i].end.y;
			uv_end.y = (world.room->ceil_h * distance) / world.room->proj_walls[i].end.y;
			ft_printf("start:%d|%d, end:%d|%d\n", uv_start.x, uv_start.y, uv_end.x, uv_end.y);
			draw_rays(buf, uv_start, uv_end, world.room->walls[i].color);
			//draw_pixel(uv_start.x, uv_start.y, buf, room->walls[i].color);
		//	draw_pixel(uv_end.x, uv_end.y, buf, room->walls[i].color);
		}
		i++;
	}
}*/

void	r_dotests(t_doom *doom)
{
	//draw_room3d(doom->rend.win_buffer, doom->world);
	draw_cube(doom);
	if (doom->keys.rot_switch == TRUE)
	{
		doom->world.cube_rotation.x += 0.001;
		doom->world.cube_rotation.z += 0.001;
	}
}
