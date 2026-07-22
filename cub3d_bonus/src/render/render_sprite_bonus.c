/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:15:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static unsigned int	get_anim_color(void)
{
	int64_t	t;

	t = (get_time_in_ms() / 250) % 4;
	if (t == 0)
		return (0x00FF3333);
	if (t == 1)
		return (0x00FF9900);
	if (t == 2)
		return (0x00FFFF00);
	return (0x00FF00AA);
}

static void	draw_sprite_stripe(t_game *game, t_sprite_draw *draw, int stripe)
{
	int				y;
	unsigned int	color;

	color = get_anim_color();
	y = draw->draw_start_y;
	while (y < draw->draw_end_y)
	{
		my_mlx_pixel_put(&game->frame, stripe, y, (int)color);
		y++;
	}
}

static void	calculate_sprite_bounds(t_sprite_draw *draw)
{
	draw->draw_start_y = -draw->sprite_height / 2 + RESY / 2;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = draw->sprite_height / 2 + RESY / 2;
	if (draw->draw_end_y >= RESY)
		draw->draw_end_y = RESY - 1;
	draw->draw_start_x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_end_x >= RESX)
		draw->draw_end_x = RESX - 1;
}

void	render_enemy(t_game *game)
{
	t_sprite_draw	draw;
	double			sprite_x;
	double			sprite_y;
	int				stripe;

	sprite_x = game->enemy.x - game->player_x;
	sprite_y = game->enemy.y - game->player_y;
	draw.inv_det = 1.0 / (game->plane_x * game->dir_y
			- game->dir_x * game->plane_y);
	draw.transform_x = draw.inv_det * (game->dir_y * sprite_x
			- game->dir_x * sprite_y);
	draw.transform_y = draw.inv_det * (-game->plane_y * sprite_x
			+ game->plane_x * sprite_y);
	if (draw.transform_y <= 0)
		return ;
	draw.sprite_screen_x = (int)((RESX / 2)
			* (1 + draw.transform_x / draw.transform_y));
	draw.sprite_height = abs((int)(RESY / draw.transform_y));
	draw.sprite_width = abs((int)(RESY / draw.transform_y));
	calculate_sprite_bounds(&draw);
	stripe = draw.draw_start_x - 1;
	while (++stripe < draw.draw_end_x)
		if (draw.transform_y < game->z_buffer[stripe])
			draw_sprite_stripe(game, &draw, stripe);
}
