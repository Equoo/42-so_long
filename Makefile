NAME = so_long
CC = cc
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/

ADDFLAGS =
CFLAGS = -Wall -Wextra -Werror -MMD -mavx2 $(ADDFLAGS) -I $(INC_DIR) -I libft/headers -I minilibx-linux
LIBS = -Llibft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz -lbsd
SOLONG_SRCS =   classes/vector2d/add.c\
				classes/vector2d/dot.c\
				classes/vector2d/scale.c\
				classes/vector2d/sub.c\
				classes/vector2d/length.c\
				classes/vector2d/normalize.c\
				classes/vector2d.c\
				classes/texture/data.c\
				classes/texture.c\
            	render/pixel.c\
            	render/img.c\
            	render/colors.c\
            	render/m256_colors.c\
            	map_parser.c\
            	error.c\
            	time.c\
            	update.c\
            	so_long.c\

OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SOLONG_SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SOLONG_SRCS)}
-include $(DEPS)

.SILENT:

.PHONY: all
all:
	$(MAKE) -j --no-print-directory ADDFLAGS="-O3" SOLONG_SRCS="$(SOLONG_SRCS)" $(NAME)

.PHONY: debug
debug:
	$(MAKE) -j --no-print-directory ADDFLAGS="-O0 -g3" SOLONG_SRCS="$(SOLONG_SRCS)" $(NAME)

.PHONY: bonus
bonus:
	$(MAKE) --no-print-directory ADDFLAGS="-O3" SOLONG_SRCS="$(SRCS_BONUS)"

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	echo "Compiling $*.c"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	echo "Make libft"
	$(MAKE) -s -j -C ./libft

$(MLX):
	$(MAKE) -s -j -C ./minilibx-linux

$(NAME): $(MLX) $(LIBFT) $(DIR_OBJ) $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(MAKE) -j clean --no-print-directory -C ./minilibx-linux
	$(MAKE) -j clean --no-print-directory -C ./libft
	rm -Rf $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	$(MAKE) -j fclean --no-print-directory -C ./libft
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) -j --no-print-directory fclean
	$(MAKE) --no-print-directory all

.DEFAULT_GOAL = all
