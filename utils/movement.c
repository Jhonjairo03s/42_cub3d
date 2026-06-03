/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/03 00:00:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/include/MLX42/MLX42.h"
#include <math.h>

void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
	game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(rot_speed)
		- game->plane_y * sin(rot_speed);
	game->plane_y = old_plane_x * sin(rot_speed)
		+ game->plane_y * cos(rot_speed);
}

void	update_view(t_game *game)
{
	double	rot_speed;

	rot_speed = 2.0 * game->mlx->delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		rotate_player(game, -rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		rotate_player(game, rot_speed);
}

static void	move_player(t_game *game, double move_x, double move_y)
{
	int	map_x;
	int	map_y;
	int	new_map_x;
	int	new_map_y;

	new_map_x = (int)(game->player_x + move_x);
	map_y = (int)game->player_y;
	if (new_map_x >= 0 && new_map_x < game->map_width
		&& map_y >= 0 && map_y < game->map_height)
	{
		if (game->map[map_y * game->map_width + new_map_x] != '1')
			game->player_x += move_x;
	}
	map_x = (int)game->player_x;
	new_map_y = (int)(game->player_y + move_y);
	if (map_x >= 0 && map_x < game->map_width
		&& new_map_y >= 0 && new_map_y < game->map_height)
	{
		if (game->map[new_map_y * game->map_width + map_x] != '1')
			game->player_y += move_y;
	}
}

void	update_movement(t_game *game)
{
	double	move_speed;

	move_speed = 3.0 * game->mlx->delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		move_player(game, game->dir_x * move_speed, game->dir_y * move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		move_player(game, -game->dir_x * move_speed, -game->dir_y * move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		move_player(game, game->dir_y * move_speed, -game->dir_x * move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		move_player(game, -game->dir_y * move_speed, game->dir_x * move_speed);
}

void	update_player(t_game *game)
{
	update_view(game);
	update_movement(game);
}
