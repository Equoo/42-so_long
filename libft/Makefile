NAME = libft.a
CC = cc
AR = ar -rcs
CFLAGS = -Wall -Wextra -Werror -MMD -I .
SRCS = ft_isalnum.c\
       ft_isalpha.c\
	   ft_isascii.c\
	   ft_isdigit.c\
	   ft_isprint.c\
	   ft_strlen.c\
	   ft_memset.c\
	   ft_bzero.c\
	   ft_memmove.c\
	   ft_memcpy.c\
	   ft_strlcpy.c\
	   ft_strlcat.c\
	   ft_toupper.c\
	   ft_tolower.c\
	   ft_strchr.c\
	   ft_strrchr.c\
	   ft_strchrpos.c\
	   ft_strncmp.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_strnstr.c\
	   ft_atoi.c\
	   ft_calloc.c\
	   ft_strdup.c\
	   ft_substr.c\
	   ft_strjoin.c\
	   ft_strtrim.c\
	   ft_split.c\
	   ft_itoa.c\
	   ft_strmapi.c\
	   ft_striteri.c\
	   ft_putchar_fd.c\
	   ft_putstr_fd.c\
	   ft_putendl_fd.c\
	   ft_putnbr_fd.c\
       ft_lstnew.c\
	   ft_lstadd_front.c\
	   ft_lstsize.c\
	   ft_lstlast.c\
	   ft_lstadd_back.c\
	   ft_lstdelone.c\
	   ft_lstclear.c\
	   ft_lstiter.c\
	   ft_lstmap.c\
	   ft_isspace.c\
	   ft_atoll.c\
	   printf_converts.c\
	   printf_nbrtostr.c\
	   printf_utils.c\
	   printf_float.c\
	   ft_printf.c\
	   get_next_line_utils.c\
	   get_next_line.c

DIR_OBJ = obj/
OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SRCS_ALL)}
-include $(DEPS)

.PHONY: all
all: $(NAME)

$(DIR_OBJ):
	mkdir -p $@

$(DIR_OBJ)%.o: %.c Makefile
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