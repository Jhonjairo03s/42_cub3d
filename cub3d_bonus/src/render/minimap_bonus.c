/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:40:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/07/22 17:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#define RADAR_R 55
#define RADAR_CX 70
#define RADAR_CY 70

static int	get_radar_color(t_game *game, double wx, double wy)
{
	int		mx;
	int		my;
	char	tile;

	mx = (int)wx;
	my = (int)wy;
	if (mx < 0 || mx >= game->map_width || my < 0 || my >= game->map_height)
		return (0x111122);
	tile = game->map[my * game->map_width + mx];
	if (tile == '1')
		return (0x445577);
	if (tile == '0')
		return (0x222233);
	if (tile == 'D')
		return (0xAA6622);
	if (tile == 'O')
		return (0x22AA66);
	return (0x111122);
}

static void	draw_radar_border(t_game *game)
{
	int		d[2];
	int		dist_sq;
	double	nx;
	double	ny;

	d[1] = -RADAR_R - 2;
	while (++d[1] <= RADAR_R + 2)
	{
		d[0] = -RADAR_R - 2;
		while (++d[0] <= RADAR_R + 2)
		{
			dist_sq = d[0] * d[0] + d[1] * d[1];
			if (dist_sq >= RADAR_R * RADAR_R
				&& dist_sq <= (RADAR_R + 3) * (RADAR_R + 3))
				my_mlx_pixel_put(&game->frame, RADAR_CX + d[0],
					RADAR_CY + d[1], 0x00FFCC);
		}
	}
	nx = -game->dir_y;
	ny = -game->dir_x;
	my_mlx_pixel_put(&game->frame, RADAR_CX + (int)(nx * RADAR_R),
		RADAR_CY + (int)(ny * RADAR_R), 0xFF0000);
}

static void	draw_radar_pixels(t_game *game)
{
	int		d[2];
	double	world[2];
	double	scale;

	scale = 0.12;
	d[1] = -RADAR_R;
	while (d[1] <= RADAR_R)
	{
		d[0] = -RADAR_R;
		while (d[0] <= RADAR_R)
		{
			if (d[0] * d[0] + d[1] * d[1] < RADAR_R * RADAR_R)
			{
				world[0] = game->player_x + (d[0] * game->plane_x
						+ d[1] * game->dir_x) * scale;
				world[1] = game->player_y + (d[0] * game->plane_y
						+ d[1] * game->dir_y) * scale;
				my_mlx_pixel_put(&game->frame, RADAR_CX + d[0],
					RADAR_CY + d[1], get_radar_color(game,
						world[0], world[1]));
			}
			d[0]++;
		}
		d[1]++;
	}
}

static void	draw_center_player(t_game *game)
{
	int	x;
	int	y;

	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			if (x * x + y * y <= 4)
				my_mlx_pixel_put(&game->frame, RADAR_CX + x,
					RADAR_CY + y, 0xFF0055);
			x++;
		}
		y++;
	}
	my_mlx_pixel_put(&game->frame, RADAR_CX, RADAR_CY - 3, 0xFFFF00);
	my_mlx_pixel_put(&game->frame, RADAR_CX, RADAR_CY - 4, 0xFFFF00);
	my_mlx_pixel_put(&game->frame, RADAR_CX, RADAR_CY - 5, 0xFFFF00);
}

void	render_minimap(t_game *game)
{
	draw_radar_pixels(game);
	draw_radar_border(game);
	draw_center_player(game);
}
