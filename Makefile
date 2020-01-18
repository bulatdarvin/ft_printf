# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 20:10:22 by ssilvana          #+#    #+#              #
#    Updated: 2019/12/22 17:27:40 by ssilvana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc -Wall -Wextra -Werror

SRCS_FILES = types/chars.c \
	  types/float.c \
	  types/numbers.c \
	  types/others.c \
	  types/wchars.c \
	  types/help_to_numbers.c \
	  types/longs.c \
	  types/wstring.c \
	  flag.c \
	  ft_write.c \
	  main.c \
	  util.c

SRCS_PATH = ./srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJECTS_PATH = ./objs/
OBJECTS_FILES = $(SRCS_FILES:.c=.o)
OBJECTS = $(addprefix $(OBJECTS_PATH), $(OBJECTS_FILES))
 
INCLUDES = -I includes/struct.h -I libft/libft.h

LIB_SRCS_PATH=./libft/

LIB_SRCS_FILES= ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memccpy.c \
	  ft_memmove.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strlen.c \
	  ft_strdup.c \
	  ft_strnew.c \
	  ft_memalloc.c \
	  ft_strcpy.c \
	  ft_strncpy.c \
	  ft_strcat.c \
	  ft_strncat.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strstr.c \
	  ft_strnstr.c \
	  ft_strcmp.c \
	  ft_strncmp.c \
	  ft_isalpha.c \
	  ft_isalnum.c \
	  ft_memdel.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
	  ft_strjoin.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putendl.c \
	  ft_putnbr.c \
	  ft_isdigit.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_atoi.c \
	  ft_strlcat.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_itoa.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_lstnew.c \
	  ft_lstdelone.c \
	  ft_lstdel.c \
	  ft_lstadd.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_sqrt.c \
	  ft_memdeltab.c \
	  ft_itoa_base.c


LIB_SRCS=$(addprefix $(LIB_SRCS_PATH), $(LIB_SRCS_FILES))

LIB_OBJECTS_PATH=./objs/
LIB_OBJECTS_FILES=$(LIB_SRCS_FILES:.c=.o)
LIB_OBJECTS=$(addprefix $(LIB_OBJECTS_PATH), $(LIB_OBJECTS_FILES))

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB_OBJECTS)
	@ar rc $(NAME) $(OBJECTS) $(LIB_OBJECTS)

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@mkdir $(OBJECTS_PATH)types 2>/dev/null || echo "" > /dev/null
	@$(CC) -c $< -o $@

$(LIB_OBJECTS_PATH)%.o: $(LIB_SRCS_PATH)%.c
	@mkdir $(LIB_OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@$(CC)  -c $< -o $@

clean:
	@/bin/rm -f $(OBJECTS) 
	@/bin/rm -rf $(OBJECTS_PATH) 
	@/bin/rm -f *.h.gch
	@/bin/rm -f .*.swp
	@/bin/rm -f $(LIB_SRCS:.c=.o)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
