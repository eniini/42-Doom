#include <fcntl.h>
#include <stdint.h>

#include "doom.h"

/*
typedef struct s_tgainfo {
	unsigned char	id;
	unsigned char	colormap;
	unsigned char	imgfield;
	int				colormap_entry;
	int				colormap_length;
	int				colormap_bpp;
	int				x_origin;
	int				y_origin;
	int				img_w;
	int				img_h;
	int				img_bpp;
	int				img_descriptor;
}				t_tgainfo;
*/

t_imgdata 	*load_file(const char *filepath)
{
	int				fd;
	unsigned char	header[18];
//	t_tgainfo		data;
	t_imgdata		*img;
	ssize_t			img_size;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (read(fd, header, 18) != 18)
		return (NULL);
	img = malloc(sizeof(t_imgdata));
	if (!img)
		return (NULL);

	ft_printf("[imgtype:%d][bytedepth:%d][descriptorbyte:%#x]", header[0x02], header[0x10], header[0x11]);
	ft_printf("[imgw:%d | imgh:%d]\n", header[0x0C] | header[0x0D] << 8 , header[0x0E] | header[0x0F] << 8 );
	
	img->w = header[0x0C] | header[0x0D] << 8;
	img->h = header[0x0E] | header[0x0F] << 8;
	img->bpp = header[0x10];
	if (img->bpp != 32) //only support 32 bits for now (transparency!)
	{
		ft_putendl("wrong bpp");
		return (NULL);
	}
	img_size = img->w * img->h * (img->bpp / 8);
	img->data = malloc(sizeof(unsigned char) * img_size);
	if (!img->data)
	{
		ft_putendl("mailloc failed");
		return (NULL);
	}
	if (read(fd, img->data, img_size) != img_size)
	{
		free(img->data);
		free(img);
		return (NULL);
	}
	if (close(fd) != 0)
		return (NULL);
	return (img);
}