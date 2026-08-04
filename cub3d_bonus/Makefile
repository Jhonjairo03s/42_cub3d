# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/27 23:59:32 by jhvalenc          #+#    #+#              #
#    Updated: 2026/07/28 17:27:00 by jhvalenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D_bonus
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -Iinc -Ilib/MLX42/include/MLX42 -Ilib/libft

LIBFT_DIR   = lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = lib/MLX42
MLX_BUILD   = $(MLX_DIR)/build
MLX42       = $(MLX_BUILD)/libmlx42.a

SRCS        = src/main.c \
              src/init/init_game.c \
              src/init/init_player.c \
              src/parse/map_validation.c \
              src/parse/program_validation.c \
              src/raycast/raycast_calc.c \
              src/raycast/dda.c \
              src/render/draw_walls.c \
              src/render/textures.c \
              src/render/minimap_bonus.c \
              src/render/fps_bonus.c \
              src/events/key_hooks.c \
              src/events/movement.c \
              src/events/mouse_bonus.c \
              src/utils/dump_and_fill.c \
              src/utils/errors.c \
              src/utils/extract_texture_path.c \
              src/utils/ft_atoi_rgb.c \
              src/utils/iterative_flood_fill.c \
              src/utils/load_texture.c \
              src/utils/map_measurement.c \
              src/utils/map_of_the_char.c \
              src/utils/parse_tex_color.c

OBJS_DIR    = obj
OBJS        = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)

all: $(LIBFT) $(MLX42) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX42):
	@cmake -B $(MLX_BUILD) -S $(MLX_DIR) > /dev/null 2>&1
	@make -C $(MLX_BUILD) -j4 > /dev/null 2>&1

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(OBJS) $(MLX42) $(MLX_BUILD)/_deps/glfw-build/src/libglfw3.a -L$(LIBFT_DIR) -lft -ldl -pthread -lm -lX11 -o $(NAME)

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@rm -rf $(MLX_BUILD) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re
