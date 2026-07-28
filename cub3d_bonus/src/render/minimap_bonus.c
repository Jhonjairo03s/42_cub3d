/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 20:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:27:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_u32	get_radar_color(t_game *game, t_i32 map_x, t_i32 map_y)
{
	t_u8	tile;

	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (0x1A202CEE);
	tile = game->map[map_y * game->map_width + map_x];
	if (tile == '1')
		return (0x4A5568FF);
	if (tile != ' ')
		return (0x2D3748DD);
	return (0x1A202CEE);
}

static void	draw_radar_pixel(t_game *game, t_i32 x, t_i32 y, t_i32 dist_sq)
{
	t_i32	map_x;
	t_i32	map_y;
	t_u32	color;

	if (dist_sq >= 76 * 76 && dist_sq <= 80 * 80)
		my_mlx_pixel_put(game->canvas, x, y, 0xCBD5E0FF);
	else if (dist_sq < 76 * 76)
	{
		map_x = (t_i32)(game->player_x + (x - MINIMAP_POS_X) / 10.0);
		map_y = (t_i32)(game->player_y + (y - MINIMAP_POS_Y) / 10.0);
		color = get_radar_color(game, map_x, map_y);
		my_mlx_pixel_put(game->canvas, x, y, color);
	}
}

static void	draw_radar_circle(t_game *game)
{
	t_i32	y;
	t_i32	x;
	t_i32	dist_sq;

	y = MINIMAP_POS_Y - MINIMAP_RADIUS;
	while (y <= MINIMAP_POS_Y + MINIMAP_RADIUS)
	{
		x = MINIMAP_POS_X - MINIMAP_RADIUS;
		while (x <= MINIMAP_POS_X + MINIMAP_RADIUS)
		{
			dist_sq = (x - MINIMAP_POS_X) * (x - MINIMAP_POS_X)
				+ (y - MINIMAP_POS_Y) * (y - MINIMAP_POS_Y);
			draw_radar_pixel(game, x, y, dist_sq);
			x++;
		}
		y++;
	}
}

static void	draw_player_icon(t_game *game)
{
	t_i32	i;
	t_i32	j;
	t_i32	dx;
	t_i32	dy;

	i = -3;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			if (i * i + j * j <= 9)
				my_mlx_pixel_put(game->canvas, MINIMAP_POS_X + i,
					MINIMAP_POS_Y + j, 0xE53E3EFF);
			j++;
		}
		i++;
	}
	i = 0;
	while (++i <= 14)
	{
		dx = MINIMAP_POS_X + (t_i32)(game->dir_x * i);
		dy = MINIMAP_POS_Y + (t_i32)(game->dir_y * i);
		my_mlx_pixel_put(game->canvas, dx, dy, 0xFFFFFFFF);
	}
}

void	draw_minimap(t_game *game)
{
	if (!game || !game->canvas || !game->map)
		return ;
	draw_radar_circle(game);
	draw_player_icon(game);
}
