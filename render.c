/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 12:00:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	ray_init_dist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player_y)
			* ray->delta_dist_y;
	}
}

static void	ray_init(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)RESX - 1;
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	ray->hit = 0;
	ray_init_dist(game, ray);
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x >= 0 && ray->map_x < game->map_width
			&& ray->map_y >= 0 && ray->map_y < game->map_height)
		{
			if (game->map[ray->map_y * game->map_width + ray->map_x] == '1')
				ray->hit = 1;
		}
		else
			ray->hit = 1;
	}
}

static void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(RESY / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + RESY / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + RESY / 2;
	if (ray->draw_end >= RESY)
		ray->draw_end = RESY - 1;
	ray->color = 0xFFFFFFFF;
	if (ray->side == 1)
		ray->color = 0xCCCCCCFF;
}

void	render(t_game *game)
{
	int		x;
	int		y;
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
		y = ray.draw_start;
		while (y <= ray.draw_end)
		{
			mlx_put_pixel(game->img, x, y, ray.color);
			y++;
		}
		x++;
	}
	render_enemy(game);
}
