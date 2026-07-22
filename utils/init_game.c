/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 21:55:10 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/20 18:09:32 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
