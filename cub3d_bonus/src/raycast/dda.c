/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:30:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:27:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	step_ray(t_ray *ray)
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
}

void	perform_dda(t_game *game, t_ray *ray)
{
	t_u8	tile;

	while (ray->hit == 0)
	{
		step_ray(ray);
		if (ray->map_x < 0 || ray->map_x >= game->map_width
			|| ray->map_y < 0 || ray->map_y >= game->map_height)
		{
			ray->hit = 1;
			break ;
		}
		tile = game->map[ray->map_y * game->map_width + ray->map_x];
		if (tile == '1')
			ray->hit = 1;
	}
}
