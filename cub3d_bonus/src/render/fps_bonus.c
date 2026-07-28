/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 20:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:34:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_glyph(t_game *game, t_i32 x, t_i32 y, t_u32 bits)
{
	t_i32	row;
	t_i32	col;

	row = 0;
	while (row < 5)
	{
		col = 0;
		while (col < 3)
		{
			if ((bits >> (14 - (row * 3 + col))) & 1)
				my_mlx_pixel_put(game->canvas, x + col, y + row, 0x00FF00FF);
			col++;
		}
		row++;
	}
}

static t_u32	get_digit_bits(t_i32 d)
{
	static const t_u32	g[10] = {
		0x7B6F, 0x2C92, 0x73E7, 0x73CF, 0x5BC9,
		0x79CF, 0x79EF, 0x7249, 0x7BEF, 0x7BC9
	};

	if (d >= 0 && d <= 9)
		return (g[d]);
	return (0);
}

static void	draw_number(t_game *game, t_i32 x, t_i32 y, t_i32 num)
{
	if (num < 0)
		num = 0;
	if (num > 99)
		num = 99;
	draw_glyph(game, x, y, get_digit_bits(num / 10));
	draw_glyph(game, x + 4, y, get_digit_bits(num % 10));
}

void	draw_fps(t_game *game)
{
	t_i32	fps;

	if (!game || !game->canvas || !game->mlx || !game->show_fps)
		return ;
	if (game->mlx->delta_time > 0)
		fps = (t_i32)(1.0 / game->mlx->delta_time);
	else
		fps = 60;
	draw_glyph(game, RESX - 40, 15, 0x7924);
	draw_glyph(game, RESX - 35, 15, 0x7B29);
	draw_glyph(game, RESX - 30, 15, 0x79CE);
	my_mlx_pixel_put(game->canvas, RESX - 25, 16, 0x00FF00FF);
	my_mlx_pixel_put(game->canvas, RESX - 25, 18, 0x00FF00FF);
	draw_number(game, RESX - 22, 15, fps);
}
