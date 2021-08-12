#include <unistd.h>
#include <fcntl.h>
#include "doom.h"

/*
*	Reading all of the assumed pixel data fromt the file into the buffer.
*	Each 4 bytes is stored into a single hexadecimal (ARGB) value.
*	Returns TRUE if pixel data loading is successful.
*/
static t_bool	load_data(t_imgdata *img, int fd)
{
	ssize_t		readbytes;
	uint32_t	i;
	char		*rawdata;
	ssize_t		img_size;

	readbytes = 0;
	i = 0;
	img_size = img->w * img->h * (img->bpp / 8);
	rawdata = (char *)malloc(img_size);
	img->data = (uint32_t *)malloc(sizeof(uint32_t) * img->w * img->h);
	if (!img->data || !rawdata)
		return (FALSE);
	if (read(fd, rawdata, img_size) != img_size)
		return (FALSE);
	while (readbytes < img_size)
	{
		img->data[i++] = (rawdata[readbytes + 3] & 255) << 24 | \
		(rawdata[readbytes + 2] & 255) << 16 | \
		(rawdata[readbytes + 1] & 255) << 8 | (rawdata[readbytes] & 255);
		readbytes += 4;
	}
	free(rawdata);
	if (close(fd) != 0)
		return (FALSE);
	return (TRUE);
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
	if (!load_data(img, fd))
		return (NULL);
	return (img);
}

/*
*	Takes in a writeable file descriptor for the resource file.
*	Returns 0 if [fd] can't be opened, tga file can't be accessed or read
*	or if writing to the resource file fails.
*	Otherwise returns the amount of bytes written.
*/
uint32_t	load_tga_info_rf(const char *filepath, int rf_fd, uint32_t offset)
{
	int				tga_fd;
	char			*buffer;
	ssize_t			retval;
	unsigned char	header[18];
	ssize_t			imgbytesize;

	tga_fd = open(filepath, O_RDONLY);
	if (tga_fd <= 0 || rf_fd <= 0)
		return (FALSE);
	if (read(tga_fd, header, 18) != 18)
		return (FALSE);
	imgbytesize = ((header[0x0C] | header[0x0D] << 8) * \
		(header[0x0E] | header[0x0F] << 8) * (header[0x10] / 8)) + 18;
	buffer = malloc(imgbytesize);
	if (!buffer)
		return (FALSE);
	lseek(tga_fd, 0, SEEK_SET);
	if (read(tga_fd, (void *)buffer, imgbytesize) != imgbytesize)
		return (FALSE);
	lseek(rf_fd, offset, SEEK_SET);
	retval = write(rf_fd, (void *)buffer, imgbytesize);
	free(buffer);
	if (retval != imgbytesize || retval - 1)
		return (FALSE);
	return ((uint32_t)retval);
}

/*
*	Loads TGA from a resource file.
*	Assumes that [fd] points at the first byte of the image header data.
*/
t_imgdata	*load_tga_from_rf(int fd)
{
	unsigned char	header[18];
	t_imgdata		*img;

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
	if (!load_data(img, fd))
		return (NULL);
	return (img);
}
