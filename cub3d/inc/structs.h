/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:59:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 15:47:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>
# include <stdbool.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef uint8_t		t_u8;
typedef uint32_t	t_u32;
typedef int32_t		t_i32;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	t_i32	map_x;
	t_i32	map_y;
	t_i32	step_x;
	t_i32	step_y;
	t_i32	hit;
	t_i32	side;
	t_i32	line_height;
	t_i32	draw_start;
	t_i32	draw_end;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*canvas;
	mlx_texture_t	*tex_n;
	mlx_texture_t	*tex_s;
	mlx_texture_t	*tex_e;
	mlx_texture_t	*tex_w;
	t_u8			*map;
	char			*raw_data;
	double			player_x;
	double			player_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	t_u32			floor_color;
	t_u32			ceil_color;
	t_i32			map_width;
	t_i32			map_height;
	t_keys			keys;
}	t_game;

typedef struct s_point
{
	t_i32	x;
	t_i32	y;
}	t_point;

#endif
