NAME = so_long
CC = cc

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/

ADDFLAGS =
CFLAGS = -Wall -Wextra -Werror -MMD -mavx2 $(ADDFLAGS) -I $(INC_DIR) -I libft/headers -I minilibx-linux
LIBS = -Llibft -lft -Lminilibx-linux -lmlx -L/usr/X11/lib -lXext -lX11 -lm
SOLONG_SRCS =   classes/vector2d/add.c\
				classes/vector2d/dot.c\
				classes/vector2d/scale.c\
				classes/vector2d/sub.c\
				classes/vector2d/length.c\
				classes/vector2d/normalize.c\
				classes/vector2d/multiply.c\
				classes/vector2d/divide.c\
				classes/vector2d/scaled.c\
				classes/vector2d/scale_divided.c\
				classes/vector2d/convert.c\
				classes/vector2d/transform.c\
				classes/vector2d.c\
				classes/texture/data.c\
				classes/texture/draw_slice.c\
				classes/texture/get_frame.c\
				classes/texture/texture_slice_time.c\
				classes/texture.c\
				classes/element.c\
				classes/terrain/draw.c\
				classes/terrain/load.c\
				classes/terrain/collide.c\
				classes/terrain/findpath.c\
				classes/terrain.c\
				classes/entity/physic.c\
				classes/entity.c\
				classes/player.c\
				classes/scene.c\
				classes/background.c\
				classes/actor/draw.c\
				classes/actor/move.c\
				classes/actor.c\
            	render/pixel.c\
            	render/copy.c\
            	render/fast_copy.c\
            	render/blend.c\
            	render/fast_blend.c\
            	render/img.c\
            	render/colors.c\
            	render/m256_colors.c\
				collisions/trace_grid.c\
				collisions/swept_aabb_grid.c\
            	error.c\
            	seed.c\
            	update.c\
            	so_long.c\

OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SOLONG_SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SOLONG_SRCS)}
-include $(DEPS)

.SILENT:

.PHONY: all
all:
	$(MAKE) -j $(nproc) --no-print-directory LIBFTTARGET="all" ADDFLAGS="-O3" SOLONG_SRCS="$(SOLONG_SRCS)" $(NAME)

.PHONY: debug
debug:
	$(MAKE) -j $(nproc) --no-print-directory LIBFTTARGET="debug" ADDFLAGS="-O0 -g3 -D DEBUG=1" SOLONG_SRCS="$(SOLONG_SRCS)" $(NAME)

.PHONY: bonus
bonus:
	$(MAKE) --no-print-directory ADDFLAGS="-O3" SOLONG_SRCS="$(SRCS_BONUS)"

.PHONY: cachegrind
cachegrind:
	valgrind --tool=cachegrind ./$(NAME) $(MAP)

.PHONY: cachegrind
callgrind:
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes ./$(NAME) $(MAP)

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	echo "Compiling $*.c"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

LIBFTTARGET = all
.PHONY: libft
libft:
	echo "Make libft"
	$(MAKE) -s -j $(nproc) -C ./libft $(LIBFTTARGET)

.PHONY: mlx
mlx:
	$(MAKE) -s -j $(nproc) -C ./minilibx-linux

$(NAME): mlx libft $(DIR_OBJ) $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(MAKE) -j $(nproc) clean --no-print-directory -C ./minilibx-linux
	$(MAKE) -j $(nproc) clean --no-print-directory -C ./libft
	rm -Rf $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	$(MAKE) -j $(nproc) fclean --no-print-directory -C ./libft
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) -j $(nproc) --no-print-directory fclean
	$(MAKE) --no-print-directory all

.DEFAULT_GOAL = all
