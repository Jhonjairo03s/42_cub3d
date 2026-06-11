/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:59:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 11:53:43 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>
# include "./mlx/include/MLX42/MLX42_Int.h"
# include "mlx/include/MLX42/MLX42.h"
# define BUFFER_SIZE 4096
# define RESX 1280
# define RESY 720

# include "./libft/libft/libft.h"
/* Error Messages */
# define ERROR_USAGE "./cub3D <maps/*name_map*.cub>\n"
# define ERROR_LENGTH "Minimum length 5 characters\n"
# define ERROR_EXTENSION "It must end in .cub\n"
# define ERROR_FD_OPEN "Error opening the file\n"
# define ERROR_FD_DIR_OPEN "It's a directory, not a map\n"

typedef uint8_t		t_u8;	// usigned char
typedef uint32_t	t_u32;	// usigned int
typedef int32_t		t_i32;	// int

typedef struct s_frame
{
	// Variables con coma flotante (8 bytes)
	double	frame_times[5];
	double	time;
	// Enteros 32 bits (4 bytes)
	t_i32	count;
}	t_frame;

typedef struct s_ray
{
	// Variables con coma flotante (8 bytes)
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	// Enteros 32 bits (4 bytes)
	t_i32	map_x;
	t_i32	map_y;
	t_i32	step_x;
	t_i32	step_y;
	t_i32	hit;
	t_i32	side;
	t_i32	line_height;
	t_i32	draw_start;
	t_i32	draw_end;
	t_u32	color;
}	t_ray;

typedef struct s_data
{
	// Enteros 64 bits (8 bytes)
	int64_t	last_time;
	int64_t	anim_timer;
	// Enteros 32 bits (4 bytes)
	t_i32	sprite_frame;
}	t_data;

typedef struct s_enemy
{
	// Variables con coma flotante (8 bytes)
	double	x;
	double	y;
	double	speed;
}	t_enemy;

typedef struct s_sprite_draw
{
	// Variables con coma flotante (8 bytes)
	double	inv_det;
	double	transform_x;
	double	transform_y;
	// Enteros 32 bits (4 bytes)
	t_i32	sprite_screen_x;
	t_i32	sprite_height;
	t_i32	sprite_width;
	t_i32	draw_start_x;
	t_i32	draw_end_x;
	t_i32	draw_start_y;
	t_i32	draw_end_y;
}	t_sprite_draw;

typedef struct s_game
{
	// Punteros (8 bytes)
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*fps_img;
	t_frame			*framedata;
	t_u32			*tex_n;
	t_u32			*tex_s;
	t_u32			*tex_e;
	t_u32			*tex_w;
	t_u8			*map;
	float			*z_buffer;
	// Variables con coma flotante (8 bytes)
	double			player_x;
	double			player_y;
	double			dir_x;
	double			dir_y;
	double			alpha;
	double			plane_x;
	double			plane_y;
	double			last_time;
	t_data			time_data;
	t_enemy			enemy;
	// Enteros 32 bits (4 bytes)
	t_u32			floor_color;
	t_u32			ceil_color;
	t_i32			map_width;
	t_i32			map_height;
	t_i32			prev_mouse_x;
	bool			show_fps;
}	t_game;

/*
 * utils/
*/
void	init_game(t_game *game);
void	update_player(t_game *game, long long elapsed);
int		err_msg(const char *msg, char *str, int code);
char	*parser_map(const char *buf);
char	*master_cursor(char *cursor);
char	*parse_path(t_game *game, char *map);
int		ft_atoi_rgb(char **str);
char	*framecalc(t_game *game);
int		program_validation(const char *arg);
void	render(t_game *game);
void	draw_background(t_game *game);
void	draw_fps(t_game *game);

int64_t	get_time_in_ms(void);
void	update_enemy(t_game *game, long long elapsed);
void	render_enemy(t_game *game);
void	mouse_cb(double xpos, double ypos, void *param);

#endif
