/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:47:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(mlx_image_t *img, t_i32 x, t_i32 y, t_u32 color)
{
	if (x < 0 || x >= (t_i32)img->width || y < 0 || y >= (t_i32)img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

static void	draw_column(t_game *game, t_ray *ray,
				mlx_texture_t *tex, t_i32 p[3])
{
	t_i32	y;
	double	step;
	double	pos;

	y = -1;
	while (++y < ray->draw_start)
		my_mlx_pixel_put(game->canvas, p[0], y, game->ceil_color);
	step = 1.0 * tex->height / ray->line_height;
	pos = (ray->draw_start - RESY / 2.0 + ray->line_height / 2.0) * step;
	y = ray->draw_start - 1;
	while (++y <= ray->draw_end)
	{
		p[2] = (t_i32)pos;
		pos += step;
		my_mlx_pixel_put(game->canvas, p[0], y,
			sample_texture(tex, p[1], p[2]));
	}
	y = ray->draw_end;
	while (++y < RESY)
		my_mlx_pixel_put(game->canvas, p[0], y, game->floor_color);
}

void	draw_wall_slice(t_game *game, t_ray *ray, t_i32 x)
{
	mlx_texture_t	*tex;
	double			wall_x;
	t_i32			p[3];

	p[0] = x;
	tex = select_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (!tex || tex->width == 0 || tex->height == 0)
		return ;
	p[1] = (t_i32)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		p[1] = tex->width - p[1] - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		p[1] = tex->width - p[1] - 1;
	draw_column(game, ray, tex, p);
}

static void	draw_crosshair(t_game *game)
{
	t_i32	i;

	if (!ENABLE_CROSSHAIR)
		return ;
	i = -CROSSHAIR_SIZE - 1;
	while (++i <= CROSSHAIR_SIZE)
	{
		my_mlx_pixel_put(game->canvas, RESX / 2 + i, RESY / 2,
			CROSSHAIR_COLOR);
		my_mlx_pixel_put(game->canvas, RESX / 2, RESY / 2 + i,
			CROSSHAIR_COLOR);
	}
}

void	render(t_game *game)
{
	t_i32	x;
	t_ray	ray;

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
	draw_crosshair(game);
}
