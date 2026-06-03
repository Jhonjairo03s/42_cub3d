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
// Error Messages
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
	double	frame_times[5];
	int		count;
	double	time;
}	t_frame;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_u32	color;
}	t_ray;

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
	// Variables con coma flotante (8 bytes)
	double			player_x;
	double			player_y;
	double			dir_x;
	double			dir_y;
	double			alpha;
	double			plane_x;
	double			plane_y;
	double			last_time;
	// Enteros 32 bits (4 bytes)
	t_u32			floor_color;
	t_u32			ceil_color;
	t_i32			map_width;
	t_i32			map_height;
	bool			show_fps;
}	t_game;

/*
 * utils/
*/
void	init_game(t_game *game);
void	update_player(t_game *game);
int		err_msg(const char *msg, char *str, int code);
char	*parser_map(const char *buf);
// char	*explore_map_north(char *map);
// char	*explore_map_south(char *map);
// char	*explore_map_east(char *map);
// char	*explore_map_west(char *map);
// char	*texture_extraction_north(char *extraction);
// char	*texture_extraction_south(char *extraction);
// char	*texture_extraction_east(char *extraction);
// char	*texture_extraction_west(char *extraction);
// char	*explore_map(char *map, const char *prefix);
// char	*extract_texture_path(char *extraction);
char	*master_cursor(char *cursor);
char	*parse_path(t_game *game, char *map);
int		ft_atoi_rgb(char **str);
char	*framecalc(t_game *game);
int		program_validation(const char *arg);
void	render(t_game *game);
void	draw_background(t_game *game);
void	draw_fps(t_game *game);

#endif
