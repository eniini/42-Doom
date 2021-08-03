#include <unistd.h>
#include <fcntl.h>
#include "doom.h"

/*
*	Reading all of the assumed pixel data fromt the file into the buffer.
*	Each 4 bytes is stored into a single hexadecimal (ARGB) value.
*/
static t_imgdata	*load_data(t_imgdata *img, int fd)
{
	ssize_t		readbytes;
	uint32_t	i;
	char		*rawdata;
	ssize_t		img_size;

	readbytes = 0;
	i = 0;
	img_size = img->w * img->h * (img->bpp / 8);
	rawdata = malloc(img_size);
	img->data = malloc(sizeof(uint32_t) * img->w * img->h);
	if (!img->data || !rawdata)
		return (NULL);
	if (read(fd, rawdata, img_size) != img_size)
		return (NULL);
	while (readbytes < img_size)
	{
		img->data[i++] = (rawdata[readbytes + 3] & 255) << 24 | \
		(rawdata[readbytes + 2] & 255) << 16 | \
		(rawdata[readbytes + 1] & 255) << 8 | (rawdata[readbytes] & 255);
		readbytes += 4;
	}
	if (close(fd) != 0)
		return (NULL);
	free(rawdata);
	return (img);
}

/*
*	Naive .TGA loading. Only supports uncompressed truecolor (32-bit) variation
*	If a wrong type of file or a malloc/IO error is encountered,
*	function returns NULL. Otherwise a pointer to [t_img] struct is returned.
*/
t_imgdata 	*load_tga(const char *filepath)
{
	int				fd;
	unsigned char	header[18];
	t_imgdata		*img;
	t_imgdata		*return_ptr;

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
	if (img->bpp != 32 || header[0x02] != 2)
	{
		free(img);
		return (NULL);
	}
	return_ptr = load_data(img, fd);
	if (!return_ptr)
		free(img);
	return (return_ptr);
}

/*	WIP !
void	*load_tga_info_wad(const char *filepath, t_struct WAD)
{
	load_tgafile();
	check_for_WAD_position();
	copy_argb_array_into_WAD_position();
	update_WAD_struct();
	
	We should probably just save the RGB-array into the WAD.
	Big question is where & how to save said imgdata's width and height.
} */
