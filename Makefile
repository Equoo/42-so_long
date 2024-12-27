NAME = so_long
CC = cc
LIB = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -MMD -lm
SOLONG_SRCS = so_long.c
DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/
OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SOLONG_SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SOLONG_SRCS)}
-include $(DEPS)

.PHONY: all
all: $(NAME)

.PHONY: bonus
bonus:
	$(MAKE) --no-print-directory SOLONG_SRCS="$(SRCS_BONUS)"

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c Makefile
	$(CC) $(CFLAGS) -I $(INC_DIR) -I libft -c $< -o $@

$(LIB):
	$(MAKE) -C ./libft

$(NAME): $(LIB) $(DIR_OBJ) $(OBJS) Makefile
	$(CC) $(CFLAGS) -I $(INC_DIR) -I libft -c $< -o $@ -Llibft -lft -lmlx

.PHONY: clean
clean:
	$(MAKE) clean --no-print-directory -C ./libft
	rm -Rf $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	$(MAKE) fclean --no-print-directory -C ./libft
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all 

.DEFAULT_GOAL = all