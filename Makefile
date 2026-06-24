export PATH := /home/pablo/cmake-bin/bin:$(PATH)

CC	:= cc
NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3
LIBMLX	:= ./mlx
LIBFT	:= ./libft

HEADERS	:= -I. -I $(LIBMLX)/include -I $(LIBFT)/libft -I ./include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -L/usr/local/lib -lglfw3 -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -ldl -pthread -lm

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

all: libmlx libft $(NAME)

libmlx:
	@mkdir -p ~/mlx_build
	@rsync -a --exclude=build $(LIBMLX)/ ~/mlx_build/
	@cmake ~/mlx_build -B ~/mlx_build/build && make -C ~/mlx_build/build -j4
	@mkdir -p $(LIBMLX)/build
	@cp ~/mlx_build/build/libmlx42.a $(LIBMLX)/build/

libft:
	@make -C $(LIBFT)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf obj
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

run: all
	@echo "Forzando X11 / OpenGL (Bypassing Wayland VSync)..."
	@env WAYLAND_DISPLAY= LIBGL_ALWAYS_SOFTWARE=1 ./$(NAME) maps/prueba.cub

.PHONY: all clean fclean re run libmlx libft
