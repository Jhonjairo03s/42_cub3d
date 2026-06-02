# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 22:42:26 by jhvalenc          #+#    #+#              #
#    Updated: 2026/06/02 11:53:33 by jhvalenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -g -Wall -Werror -Wextra

RM = rm -f

SRCS_MAIN = cub3d.c

SRCS_UTILS = init_game.c \
	     errors.c \
	     map_of_the_char.c \
	     extract_texture_path.c \
	     ft_atoi_rgb.c 

SRCS_LIBFT = ft_strlen.c \
	     ft_strcmp.c \
	     ft_strjoin.c

ALL_OBJS = $(SRCS_MAIN:.c=.o) $(SRCS_UTILS:.c=.o) $(SRCS_LIBFT:.c=.o)

all: $(NAME)

$(NAME): $(ALL_OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ALL_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
