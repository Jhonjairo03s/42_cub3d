/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 21:55:10 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_game(t_game *game)
{
	if (!game)
		return ;
	ft_memset(game, 0, sizeof(t_game));
	game->mlx_ptr = mlx_init();
	game->z_buffer = (double *)malloc(sizeof(double) * RESX);
	if (game->z_buffer)
		ft_memset(game->z_buffer, 0, sizeof(double) * RESX);
	game->prev_mouse_x = -1;
	game->enemy.x = 2.5;
	game->enemy.y = 2.5;
	game->enemy.speed = 1.0;
}

void	init_vector_n(t_game *game)
{
	game->dir_x = 0.0;
	game->dir_y = -1.0;
	game->plane_x = 0.66;
	game->plane_y = 0.0;
}

void	init_vector_s(t_game *game)
{
	game->dir_x = 0.0;
	game->dir_y = 1.0;
	game->plane_x = -0.66;
	game->plane_y = 0.0;
}

void	init_vector_e(t_game *game)
{
	game->dir_x = 1.0;
	game->dir_y = 0.0;
	game->plane_x = 0.0;
	game->plane_y = 0.66;
}

void	init_vector_w(t_game *game)
{
	game->dir_x = -1.0;
	game->dir_y = 0.0;
	game->plane_x = 0.0;
	game->plane_y = -0.66;
}
