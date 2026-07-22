# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 22:42:26 by jhvalenc          #+#    #+#              #
#    Updated: 2026/07/14 18:40:03 by jhvalenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# MLX_PATH = minilibx-linux
# MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_PATH = MLX42
MLX_LIB = $(MLX_PATH)/build/libmlx42.a
# MLX_FLAGS = -L$(MLX_PATH) -lmlx -L/usr/lib/x86_64-linux-gnu -lXext -lX11 -lm -lz
MLX_FLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm

CC = cc
# CFLAGS = -g -Wall -Werror -Wextra -I$(MLX_PATH)
CFLAGS = -g -Wall -Werror -Wextra -Iinclude -I$(MLX_PATH)/MLX42

RM = rm -f

SRCS_MAIN = cub3d.c

SRCS_PARSER = parser/map_validation.c \
	      parser/program_validation.c

SRCS_UTILS = utils/init_game.c \
	     utils/errors.c \
	     utils/map_of_the_char.c \
	     utils/extract_texture_path.c \
	     utils/ft_atoi_rgb.c \
	     utils/parse_tex_color.c \
	     utils/map_measurement.c \
	     utils/dump_and_fill.c \
	     utils/init_player.c \
	     utils/init_vectors.c \
	     utils/player_vectors.c \
	     utils/iterative_flood_fill.c

SRCS_USAGE_MLX = usage_mlx/load_texture.c

SRCS_LIBFT = libft/ft_strlen.c \
	     libft/ft_strcmp.c \
	     libft/ft_strjoin.c \
	     libft/ft_strncmp.c \
	     libft/ft_memset.c \
	     debug/debug_print_parse.c

OBJS_MAIN = $(SRCS_MAIN:.c=.o)
OBJS_UTILS = $(SRCS_UTILS:.c=.o)
OBJS_USAGE_MLX = $(SRCS_USAGE_MLX:.c=.o)
OBJS_LIBFT = $(SRCS_LIBFT:.c=.o)
OBJS_PARSER = $(SRCS_PARSER:.c=.o)

ALL_OBJS = $(OBJS_MAIN) $(OBJS_UTILS) $(OBJS_USAGE_MLX) $(OBJS_LIBFT) $(OBJS_PARSER)

all: $(NAME)

$(MLX_LIB):
	# @make -C $(MLX_PATH)
	@cmake $(MLX_PATH) -B $(MLX_PATH)/build
	@make -C $(MLX_PATH)/build -j4

$(NAME): $(ALL_OBJS) $(MLX_LIB)
	# $(CC) $(CFLAGS) $(ALL_OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $@
	$(CC) $(CFLAGS) $(ALL_OBJS) $(MLX_FLAGS) -o $@

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	# @make -C $(MLX_PATH) clean
	$(RM) $(ALL_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
