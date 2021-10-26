/*
*	Check older versions of file for the basic module/func tests!
*/

#include "doom.h"

static void	init_resources(t_doom *doom)
{
	doom->rf.fd = rf_open_resourcefile('w', "DATA");
	add_tga_to_rf(&doom->rf, "resources/dev_skybox.tga");
	rf_write_lumplist(&doom->rf);
	rf_close_fd(&doom->rf);
	doom->assets.dev_skybox = load_tga_from_rf(&doom->rf, 1);
	if (!doom->assets.dev_skybox)
		ft_getout("failed to load [dev_skybox]");
	ft_printf("asset [dev_skybox.tga] loaded successfully!\n");
	rf_free_lumplist(doom->rf.lumplist);
}

static void	init_map(t_doom *doom)
{
	int	i;

	i = 0;
	init_world(&doom->world, &doom->map, doom->rend.win_buffer);
	init_minimap(&doom->world, &doom->mmap, doom->rend.win_buffer, 2);
	while (i < doom->world.vertcount)
	{
		ft_printf("[vert %d]=[x:%+.3hd|y:%+.3hd]\n", i, \
			doom->world.p_verts[i].x, doom->world.p_verts[i].y);
		i++;
	}
	cull_vertices(&doom->world);
}

void	init_tests(t_doom *doom)
{
	doom->debug.p_angle = 0;
	doom->debug.p_fov = 60;
	doom->room = init_convex_room();
	//init_resources(doom);
	//init_map(doom);
}

void	cleanup_tests(t_doom *doom)
{
	//free(doom->room->vertices);
	//free(doom->room);
	//IF INIT_RESOURCES IS CALLED
	//free(doom->assets->dev_skybox->data);
	//free(doom->assets->dev_skybox);
	//IF INIT_MAP IS CALLED
	//free(doom->world.verts);
	//free(doom->world.p_verts);
	//free(doom->world.v_walls);
}

/*
*	draw_visibleverts(&doom->map, &doom->world);
*	draw_map(&doom->map, &doom->world);
*	draw_minimap(&doom->mmap, &doom->world);
*/
void	dotests(t_doom *doom)
{
	r_dotests(&doom->rend, doom->room, &doom->debug);
}
