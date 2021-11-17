#include "doom.h"

/*
*	Init debug buffer and static elements of debug ui to blit into it
*/
void	init_ui(t_ui *ui)
{
	ui->db_buf_stat = (t_buffer *)malloc(sizeof(t_buffer));
	if (!ui->db_buf_stat)
		ft_getout("failed to init static ui framebuffer");
	ui->db_buf_stat->w = WIN_W;
	ui->db_buf_stat->h = WIN_H;
	ui->db_buf_stat->px = ft_memalloc(sizeof(uint32_t) * WIN_H * WIN_W);
	if (!ui->db_buf_stat->px)
		ft_getout("failed to init static ui framebuffer");
	ui->db_buf_dyn = (t_buffer *)malloc(sizeof(t_buffer));
	if (!ui->db_buf_dyn)
		ft_getout("failed to init dynamic ui framebuffer");
	ui->db_buf_dyn->w = WIN_W;
	ui->db_buf_dyn->h = WIN_H;
	ui->db_buf_dyn->px = ft_memalloc(sizeof(uint32_t) * WIN_H * WIN_W);
	if (!ui->db_buf_dyn->px)
		ft_getout("failed to init dynamic ui framebuffer");
	ft_bzero(ui->ui_str, 256);
	ui->active = FALSE;
}

/*
*	Init static elements into a single buffer/img thats then stored for the
*	whole runtime and copied as necessary.
*/
void	init_debug_elements(t_ui *ui, t_assets *assets)
{
	write_to_buffer(ui->db_buf_stat, &assets->ui_text_m, \
	create_msg("FPS:", C_WHITE, (t_pixel){660, 5}));
	write_to_buffer(ui->db_buf_stat, &assets->ui_text_s, \
	create_msg("[rotation]", C_WHITE, (t_pixel){20, 10}));
	write_to_buffer(ui->db_buf_stat, &assets->ui_text_s, \
	create_msg("X:", C_WHITE, (t_pixel){20, 25}));
	write_to_buffer(ui->db_buf_stat, &assets->ui_text_s, \
	create_msg("Y:", C_WHITE, (t_pixel){20, 40}));
	write_to_buffer(ui->db_buf_stat, &assets->ui_text_s, \
	create_msg("Z:", C_WHITE, (t_pixel){20, 55}));
}

/*
*	This one handles the dynamic values (unique value per frame)
*/
static void	blit_debug_ui_vars(t_doom *doom)
{
	ft_bzero(doom->ui.db_buf_dyn->px, WIN_H * WIN_W * sizeof(uint32_t));
	ft_sprintf(doom->ui.ui_str, "%1.1f", doom->world.cube_rotation.x);
	write_to_buffer(doom->ui.db_buf_dyn, &doom->assets.ui_text_s, \
	create_msg(doom->ui.ui_str, C_TEAL, (t_pixel){45, 25}));
	ft_strclr(doom->ui.ui_str);
	ft_sprintf(doom->ui.ui_str, "%1.1f", doom->world.cube_rotation.y);
	write_to_buffer(doom->ui.db_buf_dyn, &doom->assets.ui_text_s, \
	create_msg(doom->ui.ui_str, C_TEAL, (t_pixel){45, 40}));
	ft_strclr(doom->ui.ui_str);
	ft_sprintf(doom->ui.ui_str, "%1.1f", doom->world.cube_rotation.z);
	write_to_buffer(doom->ui.db_buf_dyn, &doom->assets.ui_text_s, \
	create_msg(doom->ui.ui_str, C_TEAL, (t_pixel){45, 55}));
	ft_strclr(doom->ui.ui_str);
	ft_sprintf(doom->ui.ui_str, "%d", doom->global_fps);
	write_to_buffer(doom->ui.db_buf_dyn, &doom->assets.ui_text_m, \
	create_msg(doom->ui.ui_str, ft_color_lerp(C_RED, C_GREEN, \
	doom->global_fps / 300.0f), (t_pixel){725, 5}));
	ft_strclr(doom->ui.ui_str);
}

/*
*	Copies non-null bytes from the UI buffers into the main drawbuffer.
*/
void	blit_debug_ui(t_doom *doom)
{
	int	i;

	blit_debug_ui_vars(doom);
	i = 0;
	while (i < WIN_W * WIN_H)
	{
		if (doom->ui.db_buf_dyn->px[i] != 0)
			doom->rend.win_buffer->px[i] = doom->ui.db_buf_dyn->px[i];
		if (doom->ui.db_buf_stat->px[i] != 0)
			doom->rend.win_buffer->px[i] = doom->ui.db_buf_stat->px[i];
		i++;
	}
}
