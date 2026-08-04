/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:22:46 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/08/04 15:43:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vector_n(t_game *game)
{
	set_player_direction(game, 'N');
}

void	init_vector_s(t_game *game)
{
	set_player_direction(game, 'S');
}

void	init_vector_e(t_game *game)
{
	set_player_direction(game, 'E');
}

void	init_vector_w(t_game *game)
{
	set_player_direction(game, 'W');
}

t_i32	init_player(t_game *game)
{
	t_i32	c;
	t_i32	i;

	c = 0;
	i = -1;
	while (++i < game->map_width * game->map_height)
	{
		if (game->map[i] == 'N' || game->map[i] == 'S'
			|| game->map[i] == 'E' || game->map[i] == 'W')
		{
			game->player_x = (i % game->map_width) + 0.5;
			game->player_y = (i / game->map_width) + 0.5;
			set_player_direction(game, game->map[i]);
			game->map[i] = '0';
			c++;
		}
	}
	if (c == 0)
		return (err_msg("Init player", ERROR_NOT_PLAYER, -1));
	if (c > 1)
		return (err_msg("Init player", ERROR_MULTI_PLAYER, -1));
	return (0);
}
