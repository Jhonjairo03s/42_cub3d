/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#define PLAYER_RADIUS 0.2

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

static bool	is_solid(t_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (true);
	tile = game->map[map_y * game->map_width + map_x];
	if (tile == '1' || tile == 'D')
		return (true);
	return (false);
}

static void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	margin_x;
	double	margin_y;

	new_x = game->player_x + move_x;
	new_y = game->player_y + move_y;
	margin_x = PLAYER_RADIUS;
	if (move_x < 0)
		margin_x = -PLAYER_RADIUS;
	margin_y = PLAYER_RADIUS;
	if (move_y < 0)
		margin_y = -PLAYER_RADIUS;
	if (!is_solid(game, new_x + margin_x, game->player_y))
		game->player_x = new_x;
	if (!is_solid(game, game->player_x, new_y + margin_y))
		game->player_y = new_y;
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
