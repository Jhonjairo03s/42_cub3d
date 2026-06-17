/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:07:21 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/16 16:13:33 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
