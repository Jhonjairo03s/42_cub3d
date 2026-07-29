/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:22:46 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:41:49 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Routes the player's initial facing direction to the corresponding
 *        vector initialization function.
 *
 * @param game Pointer to the main game structure.
 * @param direction The character ('N', 'S', 'E', 'W') found on the map.
 *
 * @note These vector functions will set both the directional vector 
 *		 (dir_x, dir_y) and the camera plane vector (plane_x, plane_y) 
 *		 required for raycasting.
 */
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

/**
 * @brief Scans the 1D map array to locate the player, extracts their 
 *        coordinates, and sets up their orientation.
 * 
 * @param game Pointer to the main game structure.
 * @return int The total number of player characters found on the map.
 * 
 * @note To find the 2D (x, y) coordinates from a 1D index, we use modulo (%) 
 *       for X and division (/) for Y. Adding 0.5 places the player exactly 
 *       in the mathematical center of the tile. The player's spawn char is 
 *       then overwritten with '0' (floor) so the raycaster treats it as a 
 *       walkable space.
 */
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

/**
 * @brief Orchestrates the player initialization and validates the player count.
 *
 * @param game Pointer to the main game structure.
 * @return int 0 if exactly one player is found and successfully initialized.
 *         Returns -1 if there is no player, or if multiple spawn points exist.
 */
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
