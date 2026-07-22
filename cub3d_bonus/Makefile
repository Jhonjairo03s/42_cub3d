# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 22:42:26 by jhvalenc          #+#    #+#              #
#    Updated: 2026/07/22 16:55:00 by ppaula-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D_bonus

MLX_DIR = lib/mlx
LIBFT_DIR = lib/libft

MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -Wno-cast-function-type -Iinc -I$(MLX_DIR) -I$(LIBFT_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lz

RM = rm -rf

SRCS = src/main.c \
       src/init/init_game.c \
       src/init/init_mlx.c \
       src/parse/parse_file.c \
       src/parse/parse_map.c \
       src/parse/parse_map_size.c \
       src/parse/parse_colors.c \
       src/parse/validate_walls.c \
       src/raycast/raycast_calc.c \
       src/raycast/dda.c \
       src/render/draw_walls.c \
       src/render/textures.c \
       src/render/minimap_bonus.c \
       src/events/key_hooks.c \
       src/events/movement.c \
       src/utils/clean_exit.c \
       src/utils/error_msg.c

OBJS_DIR = obj
OBJS = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

bonus: all

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(OBJS_DIR)/%.o: src/%.c inc/cub3d.h inc/structs.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	$(RM) $(OBJS_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
