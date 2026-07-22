/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 17:07:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	toggle_door(t_game *game)
{
	int	target_x;
	int	target_y;
	int	idx;

	target_x = (int)(game->player_x + game->dir_x * 1.2);
	target_y = (int)(game->player_y + game->dir_y * 1.2);
	if (target_x >= 0 && target_x < game->map_width
		&& target_y >= 0 && target_y < game->map_height)
	{
		idx = target_y * game->map_width + target_x;
		if (game->map[idx] == 'D')
			game->map[idx] = 'O';
		else if (game->map[idx] == 'O')
			game->map[idx] = 'D';
	}
}
