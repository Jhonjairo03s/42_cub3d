/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:40:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/07/22 16:40:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	scale;
	int	offset_x;
	int	offset_y;
	int	r;
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;
	int	px;
	int	py;
	int	color;
	char	tile;

	scale = 8;
	offset_x = 15;
	offset_y = 15;
	r = 8;
	y = (int)game->player_y - r;
	while (y <= (int)game->player_y + r)
	{
		x = (int)game->player_x - r;
		while (x <= (int)game->player_x + r)
		{
			draw_x = offset_x + (x - ((int)game->player_x - r)) * scale;
			draw_y = offset_y + (y - ((int)game->player_y - r)) * scale;
			color = 0x00222222;
			if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
			{
				tile = game->map[y * game->map_width + x];
				if (tile == '1')
					color = 0x00888888;
				else if (tile == '0')
					color = 0x00444444;
				else if (tile == 'D')
					color = 0x000088FF;
				else if (tile == 'O')
					color = 0x0000FFAA;
			}
			draw_square(&game->frame, draw_x, draw_y, scale, color);
			x++;
		}
		y++;
	}
	px = offset_x + r * scale + (int)((game->player_x - (int)game->player_x) * scale);
	py = offset_y + r * scale + (int)((game->player_y - (int)game->player_y) * scale);
	draw_square(&game->frame, px - 2, py - 2, 5, 0x00FF0000);
	r = 0;
	while (r < 12)
	{
		my_mlx_pixel_put(&game->frame, px + (int)(game->dir_x * r),
			py + (int)(game->dir_y * r), 0x00FFFF00);
		r++;
	}
}
