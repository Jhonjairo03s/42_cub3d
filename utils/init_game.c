/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 21:55:10 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:35:56 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Initializes all fields of the t_game structure to safe default values.
 *
 * @param game Pointer to the main game structure to be initialized.
 *
 * @note This is a critical step for memory safety. By setting all pointers
 *       to NULL and values to 0 before any allocations occur, error handling
 *       functions (like clean_exit) can safely verify which resources need
 *       to be freed without risking "double free" or uninitialized pointer 
 *       errors.
 */
void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->tex_n = NULL;
	game->tex_s = NULL;
	game->tex_e = NULL;
	game->tex_w = NULL;
	game->map = NULL;
	game->raw_data = NULL;
	game->player_x = 0.0;
	game->player_y = 0.0;
	game->dir_x = 0.0;
	game->dir_y = 0.0;
	game->plane_x = 0.0;
	game->plane_y = 0.0;
	game->floor_color = 0;
	game->ceil_color = 0;
	game->map_width = 0;
	game->map_height = 0;
}
