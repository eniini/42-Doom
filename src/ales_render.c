#include "doom.h"

void	rotate_3d(t_fvector *start, t_fvector *end, int yaw)
{
	t_vector	result1, result2;


	result1.y = start->x * cos(yaw * DEG_TO_RAD) + start->y * sin(yaw * DEG_TO_RAD);
	result2.y = end->x * cos(yaw * DEG_TO_RAD) + end->y * sin(yaw * DEG_TO_RAD);
	result1.x = start->x * sin(yaw * DEG_TO_RAD) - start->y * cos(yaw * DEG_TO_RAD);	
	result2.x = end->x * sin(yaw * DEG_TO_RAD) - end->y * cos(yaw * DEG_TO_RAD);

	start->x = result1.x;
	start->y = result1.y;
	end->x = result2.x;
	end->y = result2.y;
}


/*
void	fp_view_map(t_doom *doom)
{
//	t_fvector	result;
	t_fvector		start, end;
	t_vector		start2, end2;
	int			i = 0;
	float		x = 1;
	t_fvector	cord[5];
	cord[0]=(t_fvector){395, 295, 0};
	cord[1]=(t_fvector){405, 205, 0};
	cord[2]=(t_fvector){405, 305, 0};
	cord[3]=(t_fvector){395, 305, 0};
	cord[4]=(t_fvector){395, 295, 0};
//	draw_circle(doom->rend.win_buffer, (t_pixel){WIN_W / 2, WIN_H / 2}, 10, MMAP_C_PLAYER);
//	draw_vector_line(doom->rend.win_buffer, (t_line){(t_vector){WIN_W/2, WIN_H/2, 0}, (t_vector){WIN_W/2, WIN_H/2 - 25, 0}}, 0xFFFFFF);
	while(i < 4)
	{
		
		start.x = (cord[i].x) * x - doom->player.pos.x;
		start.y = cord[i].y * x - doom->player.pos.y;
		end.x = (cord[i + 1].x) * x - doom->player.pos.x;
		end.y = (cord[i + 1].y) * x - doom->player.pos.y;
		rotate_3d(&start, &end, doom->player.yaw);
//		result = vector2_rotate((t_vector){start.x, start.y, 0}, (t_vector){WIN_W/2, WIN_H/2, 0}, doom->player.yaw * -1 - 90);
//		start.x = result.x;
//		start.y = result.y;
//		result = vector2_rotate((t_vector){end.x, end.y, 0}, (t_vector){WIN_W/2, WIN_H/2, 0}, doom->player.yaw * -1 - 90);
//		end.x = result.x;
//		end.y = result.y;

		start2.x = -start.x * 16 / start.y + WIN_W/2;
		start2.y = -50 / start.y + WIN_H/2;
		end2.x =  -end.x * 16 / end.y +WIN_W/2;
		end2.y = -50 /end.y + WIN_H/2;

//		printf("start.x = %f\tstart.y=%f\n", start.x, start.y);
		if(start.y > 0 || end.y > 0)
			draw_vector_line(doom->rend.win_buffer, (t_line){start2, end2}, doom->world.room->walls[i].color);
		start2.x = -start.x * 16 / start.y + WIN_W/2;
		start2.y = +50 / start.y + WIN_H/2;
		end2.x =  -end.x * 16 / end.y +WIN_W/2;
		end2.y = +50 /end.y + WIN_H/2;


		if(start.y > 0 || end.y > 0)
			draw_vector_line(doom->rend.win_buffer, (t_line){start2, end2}, doom->world.room->walls[i].color);
		i++;
	}
//	printf("player.x = %f\tplayer.y = %f\n", doom->player.pos.x, doom->player.pos.y);
//	printf("\n");
}
*/

void	centered_map(t_doom *doom)
{
	t_vector	result;
	t_vector	start;
	t_vector	end;
	t_ivec3		istart, iend;

	int			i = 0;
	float		x = 1;

	draw_circle(doom->rend.win_buffer, (t_pixel){WIN_W / 2, WIN_H / 2}, 10, C_TEAL);
	draw_vector_line(doom->rend.win_buffer, (t_line){(t_ivec3){WIN_W/2, WIN_H/2, 0}, (t_ivec3){WIN_W/2, WIN_H/2 - 25, 0}}, 0xFFFFFF);
while(i < doom->world.room->wallcount)
	{
		start.x = (doom->world.room->walls[i].start.x * x) - doom->player.pos.x + WIN_W;
		start.y = doom->world.room->walls[i].start.y * x - doom->player.pos.y + WIN_H;
		end.x = doom->world.room->walls[i].end.x * x - doom->player.pos.x + WIN_W;
		end.y = doom->world.room->walls[i].end.y * x - doom->player.pos.y + WIN_H;
		result = vector2_rotate((t_vector){start.x, start.y, 0}, (t_vector){WIN_W/2, WIN_H/2, 0}, doom->player.yaw * -1 - 90);
		start.x = result.x;
		start.y = result.y;
		result = vector2_rotate((t_vector){end.x, end.y, 0}, (t_vector){WIN_W/2, WIN_H/2, 0}, doom->player.yaw * -1 - 90);
		end.x = result.x;
		end.y = result.y;
		
		istart = (t_ivec3){start.x, start.y, 0};
		iend = (t_ivec3){end.x, end.y, 0};

		draw_vector_line(doom->rend.win_buffer, (t_line){istart, iend}, doom->world.room->walls[i].color);
		i++;
	}

}

void	map_draw(t_doom	*doom)
{
	t_pixel		start;
	t_pixel		end;
	int			i = 0;
	float		x = 1;

	draw_circle(doom->rend.win_buffer, (t_pixel){doom->player.pos.x, doom->player.pos.y}, 10, MMAP_C_PLAYER);
	dir_arrow(doom);
	while(i < doom->world.room->wallcount)
	{
		start.x = (doom->world.room->walls[i].start.x * x);
		start.y = doom->world.room->walls[i].start.y * x;
		end.x = doom->world.room->walls[i].end.x * x;
		end.y = doom->world.room->walls[i].end.y * x;

		start.x = start.x + (WIN_W / 2);
		start.y = start.y + (WIN_H / 2);
		end.x = end.x + (WIN_W / 2);
		end.y = end.y + (WIN_H / 2);
		draw_line(doom->rend.win_buffer, start, end, doom->world.room->walls[i].color);
		i++;
	}


}

void	ales_render(t_doom *doom)
{
	if(doom->keys.view_switch == 0)
		map_draw(doom);
	else if(doom->keys.view_switch == 1)
		map_draw(doom);
	else 
		centered_map(doom);
//	printf("player.x = %f\tplayer.y = %f\n", doom->player.pos.x, doom->player.pos.y);
}


