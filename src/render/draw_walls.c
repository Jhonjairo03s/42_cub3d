/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= RESX || y < 0 || y >= RESY)
		return ;
	if (!img || !img->addr)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static unsigned int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*src;

	if (!tex || !tex->addr)
		return (0x00808080);
	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	src = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)src);
}

void	draw_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_img			*tex;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	int				y;
	double			step;
	double			tex_pos;
	unsigned int	color;

	tex = select_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (tex && tex->width > 0 && tex->height > 0)
	{
		tex_x = (int)(wall_x * (double)tex->width);
		if (ray->side == 0 && ray->ray_dir_x > 0)
			tex_x = tex->width - tex_x - 1;
		if (ray->side == 1 && ray->ray_dir_y < 0)
			tex_x = tex->width - tex_x - 1;
		step = 1.0 * tex->height / ray->line_height;
		tex_pos = (ray->draw_start - RESY / 2.0 + ray->line_height / 2.0) * step;
		y = ray->draw_start;
		while (y <= ray->draw_end)
		{
			tex_y = (int)tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			tex_pos += step;
			color = get_tex_pixel(tex, tex_x, tex_y);
			my_mlx_pixel_put(&game->frame, x, y, (int)color);
			y++;
		}
	}
	else
	{
		y = ray->draw_start;
		while (y <= ray->draw_end)
		{
			my_mlx_pixel_put(&game->frame, x, y, (int)ray->color);
			y++;
		}
	}
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < RESY / 2)
	{
		x = 0;
		while (x < RESX)
		{
			my_mlx_pixel_put(&game->frame, x, y, game->ceil_color);
			x++;
		}
		y++;
	}
	while (y < RESY)
	{
		x = 0;
		while (x < RESX)
		{
			my_mlx_pixel_put(&game->frame, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

void	draw_fps(t_game *game)
{
	char	*fps_str;
	char	*tmp;
	int		fps;

	if (!game || !game->show_fps || !game->win_ptr)
		return ;
	if (game->time_data.delta_time > 0)
		fps = (int)(1.0 / game->time_data.delta_time);
	else
		fps = 0;
	tmp = ft_itoa(fps);
	if (tmp)
	{
		fps_str = ft_strjoin("FPS: ", tmp);
		free(tmp);
		if (fps_str)
		{
			mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 20,
				0x00FFFFFF, fps_str);
			free(fps_str);
		}
	}
}

static void	draw_sprite_stripe(t_game *game, t_sprite_draw *draw, int stripe)
{
	int	y;

	y = draw->draw_start_y;
	while (y < draw->draw_end_y)
	{
		my_mlx_pixel_put(&game->frame, stripe, y, 0x00FF0000);
		y++;
	}
}

static void	calculate_sprite_bounds(t_sprite_draw *draw)
{
	draw->draw_start_y = -draw->sprite_height / 2 + RESY / 2;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = draw->sprite_height / 2 + RESY / 2;
	if (draw->draw_end_y >= RESY)
		draw->draw_end_y = RESY - 1;
	draw->draw_start_x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_end_x >= RESX)
		draw->draw_end_x = RESX - 1;
}

void	render_enemy(t_game *game)
{
	t_sprite_draw	draw;
	double			sprite_x;
	double			sprite_y;
	int				stripe;

	sprite_x = game->enemy.x - game->player_x;
	sprite_y = game->enemy.y - game->player_y;
	draw.inv_det = 1.0 / (game->plane_x * game->dir_y
			- game->dir_x * game->plane_y);
	draw.transform_x = draw.inv_det * (game->dir_y * sprite_x
			- game->dir_x * sprite_y);
	draw.transform_y = draw.inv_det * (-game->plane_y * sprite_x
			+ game->plane_x * sprite_y);
	draw.sprite_screen_x = (int)((RESX / 2)
			* (1 + draw.transform_x / draw.transform_y));
	draw.sprite_height = abs((int)(RESY / draw.transform_y));
	draw.sprite_width = abs((int)(RESY / draw.transform_y));
	calculate_sprite_bounds(&draw);
	stripe = draw.draw_start_x;
	while (stripe < draw.draw_end_x)
	{
		if (draw.transform_y > 0 && game->z_buffer
			&& draw.transform_y < game->z_buffer[stripe])
			draw_sprite_stripe(game, &draw, stripe);
		stripe++;
	}
}

void	render(t_game *game)
{
	int		x;
	t_ray	ray;

	draw_background(game);
	x = 0;
	while (x < RESX)
	{
		ray_init(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_dist(&ray);
		if (game->z_buffer != NULL)
			game->z_buffer[x] = ray.perp_wall_dist;
		draw_wall_slice(game, &ray, x);
		x++;
	}
	render_enemy(game);
}
