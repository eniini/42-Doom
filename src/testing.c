/*
*	Check older versions of file for the basic module/func tests!
*/

#include "doom.h"

static void	init_resources(t_doom *doom)
{
	doom->rf.fd = rf_open_resourcefile('w', "DATA");
	add_tga_to_rf(&doom->rf, "resources/dev_skybox.tga");
	add_tga_to_rf(&doom->rf, "resources/freemono_atlas.tga");
	rf_write_lumplist(&doom->rf);
	rf_close_fd(&doom->rf);
	doom->assets.dev_skybox = load_tga_from_rf(&doom->rf, 1);
	doom->font.atlas = load_tga_from_rf(&doom->rf, 2);
	if (!doom->assets.dev_skybox)
		ft_getout("failed to load [dev_skybox]");
	ft_printf("asset [dev_skybox.tga] loaded successfully!\n");
	if (!doom->font.atlas)
		ft_getout("failed to load font atlas!");
	ft_printf("font atlas loaded successfully!\n");
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
	doom->world.room = init_convex_room();
	init_resources(doom);
	init_font_atlas(doom);
	//init_map(doom);
	doom->world.tricount = 12;
	doom->world.cube_rotation = (t_vector){1, 1, 1, 1};
	doom->world.camera = (t_vector){0, 0, 0, 1};
	doom->world.cam_fov = 90;
	doom->world.cam_distance = 16;
	doom->world.cube = (t_tri *)malloc(sizeof(t_tri) * doom->world.tricount);
	if (!doom->world.cube)
		ft_getout("failed to malloc cube!");
	//south
	doom->world.cube[0].p[0] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	doom->world.cube[0].p[1] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[0].p[2] = (t_vector){1.0f, 1.0f, 0.0f, 1};
	doom->world.cube[1].p[0] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	doom->world.cube[1].p[1] = (t_vector){1.0f, 1.0f, 0.0f, 1};
	doom->world.cube[1].p[2] = (t_vector){1.0f, 0.0f, 0.0f, 1};
	//east
	doom->world.cube[2].p[0] = (t_vector){1.0f, 0.0f, 0.0f, 1};
	doom->world.cube[2].p[1] = (t_vector){1.0f, 1.0f, 0.0f, 1};
	doom->world.cube[2].p[2] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[3].p[0] = (t_vector){1.0f, 0.0f, 0.0f, 1};
	doom->world.cube[3].p[1] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[3].p[2] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	//north
	doom->world.cube[4].p[0] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	doom->world.cube[4].p[1] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[4].p[2] = (t_vector){0.0f, 1.0f, 1.0f, 1};
	doom->world.cube[5].p[0] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	doom->world.cube[5].p[1] = (t_vector){0.0f, 1.0f, 1.0f, 1};
	doom->world.cube[5].p[2] = (t_vector){0.0f, 0.0f, 1.0f, 1};
	//west
	doom->world.cube[6].p[0] = (t_vector){0.0f, 0.0f, 1.0f, 1};
	doom->world.cube[6].p[1] = (t_vector){0.0f, 1.0f, 1.0f, 1};
	doom->world.cube[6].p[2] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[7].p[0] = (t_vector){0.0f, 0.0f, 1.0f, 1};
	doom->world.cube[7].p[1] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[7].p[2] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	//top
	doom->world.cube[8].p[0] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[8].p[1] = (t_vector){0.0f, 1.0f, 1.0f, 1};
	doom->world.cube[8].p[2] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[9].p[0] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[9].p[1] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[9].p[2] = (t_vector){1.0f, 1.0f, 0.0f, 1};
	//bottom
	doom->world.cube[10].p[0] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	doom->world.cube[10].p[1] = (t_vector){0.0f, 0.0f, 1.0f, 1};
	doom->world.cube[10].p[2] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	doom->world.cube[11].p[0] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	doom->world.cube[11].p[1] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	doom->world.cube[11].p[2] = (t_vector){1.0f, 0.0f, 0.0f, 1};
	doom->world.m_proj = mm_init_3d_projection(doom->world.cam_fov, \
	(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
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
	//write_onto_buffer(doom->rend.win_buffer, &doom->font, " !\"#$%&'()*+,-./", (t_pixel){25, 25});
	//write_onto_buffer(doom->rend.win_buffer, &doom->font, "0123456789:;<=>?@", (t_pixel){25, 50});
	//write_onto_buffer(doom->rend.win_buffer, &doom->font, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", (t_pixel){25, 75});
	//write_onto_buffer(doom->rend.win_buffer, &doom->font, "[\\]^_`", (t_pixel){25, 100});
	//write_onto_buffer(doom->rend.win_buffer, &doom->font, "abcdefghijklmnopqrstuvwxyz{|}~", (t_pixel){25, 125});
	ft_sprintf(doom->ui_str, "FOV: [%1.1f] | cube distance [%1.1f]", doom->world.cam_fov, doom->world.cam_distance);
	write_onto_buffer(doom->rend.win_buffer, &doom->font, doom->ui_str, (t_pixel){25, 25});
	r_dotests(doom);
}
