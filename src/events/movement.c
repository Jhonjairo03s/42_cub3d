/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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

void	update_player(t_game *game, double delta_time)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 3.0 * delta_time;
	rot_speed = 2.0 * delta_time;
	if (game->keys.w)
		move_player(game, game->dir_x * move_speed, game->dir_y * move_speed);
	if (game->keys.s)
		move_player(game, -game->dir_x * move_speed, -game->dir_y * move_speed);
	if (game->keys.a)
		move_player(game, game->dir_y * move_speed, -game->dir_x * move_speed);
	if (game->keys.d)
		move_player(game, -game->dir_y * move_speed, game->dir_x * move_speed);
	if (game->keys.left)
		rotate_player(game, -rot_speed);
	if (game->keys.right)
		rotate_player(game, rot_speed);
}
