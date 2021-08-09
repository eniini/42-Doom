#include "doom.h"
#include <unistd.h>
#include <fcntl.h>

/*
*	Return [fd] unless write fails
*/
int	init_resourcefile(int fd)
{
	static unsigned char	rfheader[10] = {
		'R', 'F',
		'A', 'A', 'A', 'A',
		0, 0, 0, 0,};

	if (write(fd, rfheader, 10) != 10)
		return (FALSE);
	return (fd);
}

void	update_lumpcount(int fd, uint32_t newsize)
{
	unsigned char	val[4];

	lseek(fd, 2, SEEK_SET);
	val[0] = (unsigned char)(newsize);
	val[1] = (unsigned char)(newsize >> 8);
	val[2] = (unsigned char)(newsize >> 16);
	val[3] = (unsigned char)(newsize >> 24);
	write(fd, val, 4);
}

//TODO: this should probably be ssize_t or size_t (8 bytes) //
void	update_lumplist_offset(int fd, uint32_t newpos)
{
	unsigned char	val[4];

	lseek(fd, 6, SEEK_SET);
	val[0] = (unsigned char)(newpos);
	val[1] = (unsigned char)(newpos >> 8);
	val[2] = (unsigned char)(newpos >> 16);
	val[3] = (unsigned char)(newpos >> 24);
	write(fd, val, 4);
}

/*
*	Opens the designated resource file in a desired mode.
*	Valid modes are:
*	[r] - read only
*	[w] - write only
*	[m] - read & write.
*	Returns file descriptor on success, -1 on failure.
*/
int	open_resourcefile(char openmode, char *filename)
{
	int	fd;

	fd = -1;
	if (openmode == 'r')
		fd = open(filename, O_RDONLY);
	else if (openmode == 'w')
	{
		fd = open(filename, O_WRONLY);
		if (fd == -1)
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_EXCL,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (fd != -1)
				return (init_resourcefile(fd));
		}
	}
	else if (openmode == 'm')
		fd = open(filename, O_RDWR);
	if (fd >= 0)
		return (fd);
	return (-1);
}

void	close_rf(int fd)
{
	if (close(fd) == -1)
		ft_getout(strerror(errno));
}

void	create_rf(void)
{
	int			fd;
	uint32_t	lumpcount;
	uint32_t	total_lumpsize;

	total_lumpsize = 0;
	lumpcount = 0;
	fd = open_resourcefile('w', "DATA");
	total_lumpsize += load_tga_info_rf("resources/a.tga", fd, total_lumpsize + 10);
	lumpcount++;
	update_lumpcount(fd, lumpcount);
	update_lumplist_offset(fd, total_lumpsize);
	close_rf(fd);
}

/*
*	Probably called with lump ID or something similar
*/
t_imgdata	*load_from_rf(void)
{
	int		fd;
	char	header[10];
	uint32_t	lump_count;
	uint32_t	lump_totalsize;

	fd = open_resourcefile('r', "DATA");
	if (read(fd, header, 10) != 10)
		return (FALSE);
	lump_count = header[2] | header[3] << 8 | header[4] << 16 | header[5] << 24;
	lump_totalsize = header[6] | header[7] << 8 | header[8] << 16 | header[9] << 24;
	printf("n: of lumps:%u|total bytesize of lumps:%u\n", lump_count, lump_totalsize);
	return (load_tga_from_rf(fd));
}
