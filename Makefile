NAME = so_long
CC = cc

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/

ADDFLAGS =
CFLAGS = -Wall -Wextra -Werror -MMD -mavx2 $(ADDFLAGS) -I $(INC_DIR) -I libft/headers -I minilibx-linux
LIBS = -Llibft -lft -Lminilibx-linux -lmlx -L/usr/X11/lib -lXext -lX11 -lm
SOLONG_SRCS =   vector2d/add.c\
				vector2d/dot.c\
				vector2d/scale.c\
				vector2d/sub.c\
				vector2d/length.c\
				vector2d/normalize.c\
				vector2d/multiply.c\
				vector2d/divide.c\
				vector2d/scaled.c\
				vector2d/scale_divided.c\
				vector2d/convert.c\
				vector2d/abs.c\
				vector2d/transform.c\
				vector2d/lerp.c\
				vector2d.c\
				texture/data.c\
				texture/draw_slice.c\
				texture/get_frame.c\
				texture/texture_slice_time.c\
				texture.c\
				classes/element/play_anim.c\
				classes/element.c\
				classes/terrain/grid_utils.c\
				classes/terrain/wall_rules.c\
				classes/terrain/draw.c\
				classes/terrain/load.c\
				classes/terrain/collide.c\
				classes/terrain/findpath.c\
				classes/terrain.c\
				classes/entity/physic.c\
				classes/entity.c\
				classes/player/anim_coroutine.c\
				classes/player/update.c\
				classes/player/attack.c\
				classes/player.c\
				classes/frog.c\
				scene.c\
				classes/background.c\
				classes/actor/draw.c\
				classes/actor/move.c\
				classes/actor/update.c\
				classes/actor.c\
            	render/pixel.c\
            	render/copy.c\
            	render/fast_copy.c\
            	render/blend.c\
            	render/text.c\
            	render/fast_blend.c\
            	render/img.c\
            	render/colors.c\
            	render/m256_colors.c\
				inputs/update.c\
				inputs/isdown.c\
				inputs/ispressed.c\
				inputs/isreleased.c\
				collisions/aabb.c\
				collisions/sweep_aabb.c\
				collisions/world_sweep_aabb.c\
            	error.c\
            	seed.c\
            	game.c\
            	render.c\
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

.PHONY: callgrind
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
