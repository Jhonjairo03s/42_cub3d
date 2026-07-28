/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 21:55:10 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 16:39:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	if (game == NULL)
		return ;
	ft_memset(game, 0, sizeof(t_game));
	game->prev_mouse_x = -1;
	game->mouse_enabled = true;
	game->show_fps = true;
	game->z_buffer = (double *)malloc(sizeof(double) * RESX);
	if (game->z_buffer != NULL)
		ft_memset(game->z_buffer, 0, sizeof(double) * RESX);
}
