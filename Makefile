# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 22:42:26 by jhvalenc          #+#    #+#              #
#    Updated: 2026/06/01 12:01:08 by jhvalenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -g -Wall -Werror -Wextra

RM = rm -f

SRCS = cub3d.c \
       utils/init_game.c utils/errors.c utils/map_of_the_char.c \
       utils/north_tex.c utils/south_tex.c utils/west_tex.c \
       utils/east_tex.c utils/extract_texture_path.c \
       libft/ft_strlen.c libft/ft_strcmp.c libft/ft_strjoin.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
