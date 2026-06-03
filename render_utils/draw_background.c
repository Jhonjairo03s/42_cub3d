/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:05:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 12:05:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < RESY / 2)
	{
		x = 0;
		while (x < RESX)
		{
			mlx_put_pixel(game->img, x, y, game->ceil_color);
			x++;
		}
		y++;
	}
	while (y < RESY)
	{
		x = 0;
		while (x < RESX)
		{
			mlx_put_pixel(game->img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}
