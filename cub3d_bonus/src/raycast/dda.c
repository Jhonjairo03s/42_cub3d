/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	check_dda_hit(t_game *game, t_ray *ray)
{
	char	tile;

	if (ray->map_x >= 0 && ray->map_x < game->map_width
		&& ray->map_y >= 0 && ray->map_y < game->map_height)
	{
		tile = game->map[ray->map_y * game->map_width + ray->map_x];
		if (tile == '1' || tile == 'D')
			ray->hit = 1;
	}
	else
		ray->hit = 1;
}

void	perform_dda(t_game *game, t_ray *ray)
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
		check_dda_hit(game, ray);
	}
}
