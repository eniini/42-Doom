#ifndef RESOURCEFILE_H
# define RESOURCEFILE_H

# include <stdint.h>

typedef struct s_rf_header {
	short		signature;
	int			lumpcount;
	int			lumplist_offset;
}				t_rf_header;

typedef struct s_rf_lump {
	char		type;
	size_t		id;
	size_t		offset;
	size_t		bytesize;
	void		*next;
}				t_rf_lump;

void	create_rf(void);

#endif
