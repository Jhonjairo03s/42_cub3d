/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	mouse_cb(int x, int y, t_game *game)
{
	double	mouse_delta;

	(void)y;
	if (game->prev_mouse_x == -1)
		game->prev_mouse_x = x;
	mouse_delta = x - game->prev_mouse_x;
	if (mouse_delta != 0)
	{
		rotate_player(game, mouse_delta * 0.002);
		game->prev_mouse_x = x;
	}
	return (0);
}
