#include <fcntl.h>
#include "doom.h"

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
	img->w = header[0x0C] | header[0x0D] << 8;
	img->h = header[0x0E] | header[0x0F] << 8;
	img->bpp = header[0x10];
	if (img->bpp != 32) //only support 32 bits for now (transparency!)
		return (NULL);
	if (header[0x02] != 2) //wrong TGA type (uncompressed truecolor)
		return (NULL);
	img_size = img->w * img->h * (img->bpp / 8);
	img->imgdata = malloc(sizeof(uint32_t) * img->w * img->h + 1);
	if (!img->imgdata)
		return (NULL);
	//incremental reading style
	int readbytes = 0;
	int i = 0;
	char	data[4];
	while (readbytes < img_size)
	{
		if (read(fd, data, 4) != 4L)
		{
			free(img);
			return (NULL);
		}
		img->imgdata[i++] = (data[3] & 255) << 24 | (data[2] & 255) << 16 | (data[1] & 255) << 8 | (data[0] & 255);
		readbytes += 4;
	}
	if (readbytes != img_size)
	{
		free(img->imgdata);
		free(img);
		return (NULL);
	}
	if (close(fd) != 0)
		return (NULL);
	return (img);
}