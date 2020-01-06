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

CC = gcc #-Wall -Wextra -Werror

SRCS_FILES = types/chars.c \
	  types/float.c \
	  types/numbers.c \
	  types/others.c \
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

LIB_SRCS_FILES= ft_itoa.c ft_strlen.c ft_strnstr.c ft_putchar.c ft_putendl.c ft_putstr.c ft_putnbr.c \
				ft_putchar_fd.c ft_atoi.c ft_isalnum.c ft_isdigit.c \
				ft_isalpha.c ft_itoa_base.c ft_strchr.c ft_itoa_base.c\
				ft_isprint.c ft_strnew.c ft_memalloc.c ft_bzero.c \
				ft_strcat.c ft_strsub.c ft_strncpy.c ft_strjoin.c ft_tolower.c \
				ft_strnstr.c

LIB_SRCS=$(addprefix $(LIB_SRCS_PATH), $(LIB_SRCS_FILES))

LIB_OBJECTS_PATH=./objs/
LIB_OBJECTS_FILES=$(LIB_SRCS_FILES:.c=.o)
LIB_OBJECTS=$(addprefix $(LIB_OBJECTS_PATH), $(LIB_OBJECTS_FILES))

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB_OBJECTS)
	#@make -C libft all
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
	#@make -C libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	#@make -C libft fclean

re: fclean all
