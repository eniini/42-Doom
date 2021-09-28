/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapdefs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:36:13 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 13:37:34 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPDEFS_H
# define MAPDEFS_H

# include "defines.h"

/*
*	Thing is loaded into level memory as an instance of [type] object
*	with the unique x/y-position and angle unless [flags] specify otherwise.
*
*	[!] This struct is an intermediary storage for loading from the 
*	resource file into populating the map with entities according to data
*	stored here. i.e. things -> NPCS, items, props etc...
*/
typedef struct s_me_thing {
	short	x_pos;
	short	y_pos;
	short	z_pos;
	short	angle;
	short	type;
	short	flags;
	short	id;
}			t_me_thing;
# define RF_SIZEOF_THING 14

typedef struct s_l_things {
	struct s_l_things	*next;
	struct s_me_thing	*data;
}						t_l_things;

/*
*	x/y offsets tell how many pixels all the textures are shifted.
*	On a one-sided linedef only [mid-tex] texture will be displayed.
*	Otherwise [up_tex] & [low_tex] are textures drawn onto sector offsets.
*	[s_tag] is the ID of the sector the side is facing.
*/
typedef struct s_me_sidedef {
	short	x_offs;
	short	y_offs;
	char	up_tex[8];
	char	low_tex[8];
	char	mid_tex[8];
	short	s_tag;
	short	id;
}			t_me_sidedef;
# define M_SDEF_LUMPSIZE 32

typedef struct s_l_sdefs {
	struct s_l_sdefs	*next;
	struct s_me_sidedef	*data;
}						t_l_sdefs;

/*
*	!=0 [type] indicates special functionality.
*	[s_tag] tells which sector->id the linedef is tied to.
*	-1 in either [front_sd]/[back_sd] means that the line is one-sided,
*	otherwise both are ID's to connected SIDEDEFS.
*/
typedef struct s_me_linedef {
	short			start_x;
	short			start_y;
	short			end_x;
	short			end_y;
	short			flags;
	short			type;
	short			s_tag;
	t_me_sidedef	*front_sd;
	t_me_sidedef	*back_sd;
	short			id;
}					t_me_linedef;
# define RF_SIZEOF_LINEDEF 20

typedef struct s_l_ldefs {
	struct s_l_ldefs	*next;
	struct s_me_linedef	*data;
}						t_l_ldefs;

/*
*	[lightdata] informs area brightness etc. (open for implementation)
*	[type] defines special functionality of the sector.
*	[id] gives other logic a target.
*	In practice, sector as a space only exists in relation to SIDEDEFS that
*	reference it.
*/
typedef struct s_me_sector {
	short	floor_h[4];
	short	ceil_h[4];
	char	floor_tex[8];
	char	ceil_tex[8];
	short	lightdata;
	short	type;
	short	id;
}			t_me_sector;
# define M_SEC_LUMPSIZE 38

/*
*	Soundscape is a placeholder for whatever audio we want to include.
*	Linecount tells how many LINEDEFS there are that are linked to the sector.
*	Bounding box is the total size of all areas in a single sector.
*/
typedef struct s_l_sectors {
	struct s_l_sectors	*next;
	struct s_me_sector	*data;
	void				*soundscape;
	short				linecount;
	short				boundingbox[4];
}						t_l_sectors;

typedef struct s_dbg_room {
	int			wallcount;
	t_vert		*verts;
	t_linedef	*walls;
	short		boundingbox[4];
	short		ceil_h;
	short		floor_h;
}				t_dbg_room;

t_dbg_room	*init_convex_room(void);
t_dbg_room	*init_nonconvex_room(void);

#endif