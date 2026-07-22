/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 21:55:10 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
		init_vector_n(game);
	else if (direction == 'S')
		init_vector_s(game);
	else if (direction == 'E')
		init_vector_e(game);
	else if (direction == 'W')
		init_vector_w(game);
}

static int	player_x_y(t_game *game)
{
	int	player_count;
	int	index;
	int	total_size;

	player_count = 0;
	index = 0;
	total_size = game->map_width * game->map_height;
	while (index < total_size)
	{
		if (game->map[index] == 'N' || game->map[index] == 'S'
			|| game->map[index] == 'E' || game->map[index] == 'W')
		{
			game->player_x = (index % game->map_width) + 0.5;
			game->player_y = (index / game->map_width) + 0.5;
			set_player_direction(game, game->map[index]);
			game->map[index] = '0';
			player_count++;
		}
		index++;
	}
	return (player_count);
}

int	init_player(t_game *game)
{
	int	player_count;

	player_count = player_x_y(game);
	if (player_count == 0)
		return (err_msg("Init player", ERROR_NOT_PLAYER, -1));
	if (player_count > 1)
		return (err_msg("Init player", ERROR_MULTI_PLAYER, -1));
	return (0);
}
