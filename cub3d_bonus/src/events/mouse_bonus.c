/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:55:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	mouse_cb(int x, int y, t_game *game)
{
	double	mouse_delta;

	(void)y;
	mouse_delta = x - (RESX / 2);
	if (mouse_delta != 0)
	{
		rotate_player(game, mouse_delta * 0.0015);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, RESX / 2, RESY / 2);
	}
	return (0);
}
