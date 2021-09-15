NAME	=	doom-nukem

#compiler
CC	=	gcc
LFLAGS	=	-Wall -Wextra -g #-Werror #-O3

#sources & object files
SRC_DIR =	./src/
OBJ_DIR =	./build/
SRC_LIST =	main.c \
		array_value_manip.c \
		draw_pixel.c \
		draw_line.c \
		draw_shapes.c \
		load_tga.c \
		blit.c \
		spritesheet.c \
		boids.c \
		testing.c \
		r_init.c \
		r_map.c \
		r_minimap.c \
		r_rotation.c \
		r_utility.c \
		resourcefile.c \
		rf_lump.c \
		rf_io.c \
		vec_math.c \
		vec_utility.c \
		audio.c
SRCS = $(addprefix $(SRC_DIR),$(SRC_LIST))
OBJS = $(addprefix $(OBJ_DIR),$(SRC_LIST:.c=.o))

#libft
LIBFT = libft/libft.a

#SDL2
SDL_SRC_DIR = SDL2-2.0.14
SDL_MIX_SRC_DIR = SDL2_mixer-2.0.4
SDL_DIR = libSDL2
SDL_BUILD_DIR_PATH = $(CURDIR)/$(SDL_DIR)
SDL_CFLAGS = `$(SDL_DIR)/bin/sdl2-config --cflags --libs` -lSDL2_mixer
SDL_BIN = $(SDL_DIR)/lib/libSDL2.a

.PHONY: all clean fclean re

all: $(LIBFT) $(SDL_BIN) $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(LFLAGS) -Iinclude/ -Ilibft/includes -I$(SDL_DIR)/include/SDL2 -o $@ -c $<

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(SDL_CFLAGS) -L./libft/ -lft -lm -o $(NAME)

$(SDL_BIN) :
	echo "Extracting SDL archives..."
	tar xzf SDL2-2.0.14.tar.gz
	tar xzf SDL2_mixer-2.0.4.tar.gz
	mkdir -p $(SDL_DIR)
	cd $(SDL_SRC_DIR); ./configure --prefix=$(SDL_BUILD_DIR_PATH); make -j6; make install
	cd $(SDL_MIX_SRC_DIR); ./configure --prefix=$(SDL_BUILD_DIR_PATH); make -j6; make install

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)
	rm -rf DATA

fclean: clean
	rm $(NAME)
	rm -rf $(SDL_SRC_DIR)
	rm -rf $(SDL_MIX_SRC_DIR)
	make fclean -C libft

re: fclean all
