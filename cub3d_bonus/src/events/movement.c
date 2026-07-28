/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:42:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static bool	is_free_box(t_game *game, double x, double y)
{
	t_i32	ix1;
	t_i32	ix2;
	t_i32	iy1;
	t_i32	iy2;
	t_i32	w;

	w = game->map_width;
	ix1 = (t_i32)(x - PLAYER_RADIUS);
	ix2 = (t_i32)(x + PLAYER_RADIUS);
	iy1 = (t_i32)(y - PLAYER_RADIUS);
	iy2 = (t_i32)(y + PLAYER_RADIUS);
	if (game->map[iy1 * w + ix1] == '1' || game->map[iy1 * w + ix2] == '1')
		return (false);
	if (game->map[iy2 * w + ix1] == '1' || game->map[iy2 * w + ix2] == '1')
		return (false);
	return (true);
}

static void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player_x + move_x;
	new_y = game->player_y + move_y;
	if (is_free_box(game, new_x, game->player_y))
		game->player_x = new_x;
	if (is_free_box(game, game->player_x, new_y))
		game->player_y = new_y;
}

void	update_player(t_game *game, double delta_time)
{
	double	move_speed;
	double	rot_speed;

	move_speed = MOVE_SPEED * delta_time;
	rot_speed = ROT_SPEED * delta_time;
	if (game->keys.w)
		move_player(game, game->dir_x * move_speed,
			game->dir_y * move_speed);
	if (game->keys.s)
		move_player(game, -game->dir_x * move_speed,
			-game->dir_y * move_speed);
	if (game->keys.a)
		move_player(game, game->dir_y * move_speed,
			-game->dir_x * move_speed);
	if (game->keys.d)
		move_player(game, -game->dir_y * move_speed,
			game->dir_x * move_speed);
	if (game->keys.left)
		rotate_player(game, -rot_speed);
	if (game->keys.right)
		rotate_player(game, rot_speed);
}
