/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:59:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>
# include <stdbool.h>

typedef uint8_t		t_u8;
typedef uint32_t	t_u32;
typedef int32_t		t_i32;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_frame
{
	double	frame_times[5];
	double	time;
	t_i32	count;
}	t_frame;

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
	t_u32	color;
}	t_ray;

typedef struct s_data
{
	int64_t	last_time;
	int64_t	anim_timer;
	double	delta_time;
	t_i32	sprite_frame;
}	t_data;

typedef struct s_enemy
{
	double	x;
	double	y;
	double	speed;
}	t_enemy;

typedef struct s_sprite_draw
{
	double	inv_det;
	double	transform_x;
	double	transform_y;
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
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		frame;
	t_img		*tex_n;
	t_img		*tex_s;
	t_img		*tex_e;
	t_img		*tex_w;
	t_u8		*map;
	char		*raw_data;
	double		*z_buffer;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_u32		floor_color;
	t_u32		ceil_color;
	t_i32		map_width;
	t_i32		map_height;
	t_keys		keys;
	t_frame		framedata;
	t_data		time_data;
	t_enemy		enemy;
	t_i32		prev_mouse_x;
	bool		show_fps;
}	t_game;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

#endif
