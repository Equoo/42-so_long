NAME = so_long
CC = cc
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/

CFLAGS = -Wall -Wextra -Werror -MMD -I $(INC_DIR) -I libft -I minilibx-linux
LIBS = -lXext -lX11 -Llibft -lft -Lminilibx-linux -lmlx -lm
SOLONG_SRCS = so_long.c

OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SOLONG_SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SOLONG_SRCS)}
-include $(DEPS)

.PHONY: all
all:
	$(MAKE) -j --no-print-directory SOLONG_SRCS="$(SOLONG_SRCS)" $(NAME)

.PHONY: bonus
bonus:
	$(MAKE) --no-print-directory SOLONG_SRCS="$(SRCS_BONUS)"

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -j -C ./libft

$(MLX):
	$(MAKE) -j -C ./minilibx-linux

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