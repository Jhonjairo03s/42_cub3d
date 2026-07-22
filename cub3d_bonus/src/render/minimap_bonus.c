/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:40:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_square(t_img *img, int pos[2], int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			my_mlx_pixel_put(img, pos[0] + i, pos[1] + j, color);
			j++;
		}
		i++;
	}
}

static int	get_tile_color(t_game *game, int x, int y)
{
	char	tile;

	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
	{
		tile = game->map[y * game->map_width + x];
		if (tile == '1')
			return (0x00888888);
		if (tile == '0')
			return (0x00444444);
		if (tile == 'D')
			return (0x000088FF);
		if (tile == 'O')
			return (0x0000FFAA);
	}
	return (0x00222222);
}

static void	draw_minimap_tiles(t_game *game, int offset[2], int scale, int r)
{
	int	coord[2];
	int	draw_pos[2];

	coord[1] = (int)game->player_y - r;
	while (coord[1] <= (int)game->player_y + r)
	{
		coord[0] = (int)game->player_x - r;
		while (coord[0] <= (int)game->player_x + r)
		{
			draw_pos[0] = offset[0]
				+ (coord[0] - ((int)game->player_x - r)) * scale;
			draw_pos[1] = offset[1]
				+ (coord[1] - ((int)game->player_y - r)) * scale;
			draw_square(&game->frame, draw_pos, scale,
				get_tile_color(game, coord[0], coord[1]));
			coord[0]++;
		}
		coord[1]++;
	}
}

static void	draw_player_icon(t_game *game, int offset[2], int scale, int r)
{
	int	pos[2];
	int	i;

	pos[0] = offset[0] + r * scale
		+ (int)((game->player_x - (int)game->player_x) * scale);
	pos[1] = offset[1] + r * scale
		+ (int)((game->player_y - (int)game->player_y) * scale);
	pos[0] -= 2;
	pos[1] -= 2;
	draw_square(&game->frame, pos, 5, 0x00FF0000);
	pos[0] += 2;
	pos[1] += 2;
	i = 0;
	while (i < 12)
	{
		my_mlx_pixel_put(&game->frame, pos[0] + (int)(game->dir_x * i),
			pos[1] + (int)(game->dir_y * i), 0x00FFFF00);
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	offset[2];

	offset[0] = 15;
	offset[1] = 15;
	draw_minimap_tiles(game, offset, 8, 8);
	draw_player_icon(game, offset, 8, 8);
}
