/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 18:10:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ray_init_dist(t_game *game, t_ray *ray)
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

void	ray_init(t_game *game, t_ray *ray, int x)
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

void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist < 0.05)
		ray->perp_wall_dist = 0.05;
	ray->line_height = (int)(RESY / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + RESY / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + RESY / 2;
	if (ray->draw_end >= RESY)
		ray->draw_end = RESY - 1;
	ray->color = 0x00FFFFFF;
	if (ray->side == 1)
		ray->color = 0x00CCCCCC;
}
