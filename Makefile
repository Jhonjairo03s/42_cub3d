CC	:= cc
NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3
LIBMLX	:= ./mlx
LIBFT	:= ./libft
CMAKE	:= cmake

HEADERS	:= -I. -I $(LIBMLX)/include -I $(LIBFT)/libft -I ./include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

SRCS	:= cub3d.c \
	render.c \
	render_utils/draw_background.c \
	render_utils/draw_fps.c \
	render_utils/framerate.c \
	render_utils/render_sprites.c \
	utils/init_game.c \
	utils/movement.c \
	utils/errors.c \
	utils/map_of_the_char.c \
	utils/extract_texture_path.c \
	utils/program_validation.c \
	utils/ft_atoi_rgb.c

OBJS	:= $(addprefix obj/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBMLX)/build/libmlx42.a: FORCE
	@if [ ! -f "$(LIBMLX)/CMakeLists.txt" ]; then \
		echo "MLX42 submodule not found, initializing..."; \
		git submodule update --init --recursive; \
	fi
	@$(CMAKE) $(LIBMLX) -B $(LIBMLX)/build && $(CMAKE) --build $(LIBMLX)/build -j4

$(LIBFT)/libft.a: FORCE
	@make -C $(LIBFT)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "Linking $(NAME)"

clean:
	@rm -rf obj
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE
