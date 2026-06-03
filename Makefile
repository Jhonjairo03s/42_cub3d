NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3
LIBMLX	:= ./mlx
LIBFT	:= ./libft

HEADERS	:= -I. -I $(LIBMLX)/include -I $(LIBFT)/libft
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

SRCS	:= cub3d.c \
	render.c \
	render_utils/draw_background.c \
	render_utils/draw_fps.c \
	render_utils/framerate.c \
	utils/init_game.c \
	utils/movement.c \
	utils/errors.c \
	utils/map_of_the_char.c \
	utils/extract_texture_path.c \
	utils/program_validation.c \
	utils/ft_atoi_rgb.c \
	utils/north_tex.c \
	utils/south_tex.c \
	utils/east_tex.c \
	utils/west_tex.c

OBJS	:= $(SRCS:.c=.o)

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft
