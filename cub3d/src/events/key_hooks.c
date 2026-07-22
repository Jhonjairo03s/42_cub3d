/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_press_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		clean_exit(game);
		exit(0);
	}
	if (keycode == 119 || keycode == 87)
		game->keys.w = 1;
	if (keycode == 97 || keycode == 65)
		game->keys.a = 1;
	if (keycode == 115 || keycode == 83)
		game->keys.s = 1;
	if (keycode == 100 || keycode == 68)
		game->keys.d = 1;
	if (keycode == 65361)
		game->keys.left = 1;
	if (keycode == 65363)
		game->keys.right = 1;
	if (keycode == 65472)
		game->show_fps = !game->show_fps;
	return (0);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 87)
		game->keys.w = 0;
	if (keycode == 97 || keycode == 65)
		game->keys.a = 0;
	if (keycode == 115 || keycode == 83)
		game->keys.s = 0;
	if (keycode == 100 || keycode == 68)
		game->keys.d = 0;
	if (keycode == 65361)
		game->keys.left = 0;
	if (keycode == 65363)
		game->keys.right = 0;
	return (0);
}

int	close_hook(t_game *game)
{
	clean_exit(game);
	exit(0);
	return (0);
}
