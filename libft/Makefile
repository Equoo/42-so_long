NAME = libft.a
CC = cc
AR = ar -rcs

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/

CFLAGS = -Wall -Wextra -Werror -MMD -O3 -mavx2 -I $(INC_DIR)
SRCS =	string/ft_split.c\
		string/ft_strchr.c\
		string/ft_strchrpos.c\
		string/ft_strdup.c\
		string/ft_strjoin.c\
		string/ft_strlcat.c\
		string/ft_strlcpy.c\
		string/ft_strlen.c\
		string/ft_strmapi.c\
		string/ft_strncmp.c\
		string/ft_strnstr.c\
		string/ft_strrchr.c\
		string/ft_strtrim.c\
		string/ft_substr.c\
		string/ft_stradd.c\
\
		char/ft_isalnum.c\
		char/ft_isalpha.c\
		char/ft_isascii.c\
		char/ft_isdigit.c\
		char/ft_isspace.c\
		char/ft_isprint.c\
		char/ft_tolower.c\
		char/ft_toupper.c\
\
		memory/ft_freearray.c\
		memory/ft_arraylen.c\
		memory/ft_bzero.c\
		memory/ft_calloc.c\
		memory/ft_memcpy.c\
		memory/ft_memchr.c\
		memory/ft_memcmp.c\
		memory/ft_memcpy.c\
		memory/ft_memmove.c\
		memory/ft_memset.c\
\
		list/ft_lstadd_back.c\
		list/ft_lstadd_front.c\
		list/ft_lstclear.c\
		list/ft_lstdelone.c\
		list/ft_lstiter.c\
		list/ft_lstlast.c\
		list/ft_lstmap.c\
		list/ft_lstnew.c\
		list/ft_lstsize.c\
\
		mm256/bit.c\
		mm256/math.c\
\
		convert/ft_atoi.c\
		convert/ft_atof.c\
		convert/ft_atoll.c\
		convert/ft_itoa.c\
\
		printf/converts.c\
		printf/nbrtostr.c\
		printf/utils.c\
		printf/float.c\
		printf/core.c\
\
		get_next_line/utils.c\
		get_next_line/core.c\
\
		time/ft_uptime.c

DIR_OBJ = obj/
OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SRCS_ALL)}
-include $(DEPS)

.PHONY: all
all: $(NAME)

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	echo "Compiling $*.c"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(DIR_OBJ) $(OBJS) Makefile
	$(AR) $@ $(OBJS)
	ranlib $(NAME)

.PHONY: clean
clean:
	rm -Rf $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all 

.DEFAULT_GOAL = all