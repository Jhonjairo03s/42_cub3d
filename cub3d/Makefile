# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 22:42:26 by jhvalenc          #+#    #+#              #
#    Updated: 2026/07/28 15:34:00 by jhvalenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX_DIR = lib/MLX42
LIBFT_DIR = lib/libft

MLX_LIB = $(MLX_DIR)/build/libmlx42.a
GLFW_LIB = $(MLX_DIR)/build/_deps/glfw-build/src/libglfw3.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS =  -O3 -g -g3 -Wall -Werror -Wextra -Iinc -I$(MLX_DIR)/include/MLX42 -I$(LIBFT_DIR)
MLX_FLAGS = $(MLX_LIB) $(GLFW_LIB) -L$(LIBFT_DIR) -lft -ldl -pthread -lm -lX11

RM = rm -rf

SRCS = src/main.c \
       src/init/init_mlx.c \
       src/parse/map_validation.c \
       src/parse/program_validation.c \
       src/raycast/raycast_calc.c \
       src/raycast/dda.c \
       src/render/draw_walls.c \
       src/render/textures.c \
       src/events/key_hooks.c \
       src/events/movement.c \
       src/utils/dump_and_fill.c \
       src/utils/errors.c \
       src/utils/extract_texture_path.c \
       src/utils/ft_atoi_rgb.c \
       src/utils/init_game.c \
       src/utils/init_player.c \
       src/utils/init_vectors.c \
       src/utils/iterative_flood_fill.c \
       src/utils/load_texture.c \
       src/utils/map_measurement.c \
       src/utils/map_of_the_char.c \
       src/utils/parse_tex_color.c \
       src/utils/player_vectors.c

OBJS_DIR = obj
OBJS = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build -j4

$(OBJS_DIR)/%.o: src/%.c inc/cub3d.h inc/structs.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(MLX_DIR)/build
	$(RM) $(OBJS_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
