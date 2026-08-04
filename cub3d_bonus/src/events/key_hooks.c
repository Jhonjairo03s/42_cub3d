/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/08/04 16:04:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_keys(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		return ;
	}
	game->keys.w = mlx_is_key_down(game->mlx, MLX_KEY_W);
	game->keys.s = mlx_is_key_down(game->mlx, MLX_KEY_S);
	game->keys.a = mlx_is_key_down(game->mlx, MLX_KEY_A);
	game->keys.d = mlx_is_key_down(game->mlx, MLX_KEY_D);
	game->keys.left = mlx_is_key_down(game->mlx, MLX_KEY_LEFT);
	game->keys.right = mlx_is_key_down(game->mlx, MLX_KEY_RIGHT);
}

void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	if (keydata.key == MLX_KEY_F3 && keydata.action == MLX_PRESS)
		game->show_fps = !game->show_fps;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		game->mouse_enabled = !game->mouse_enabled;
		if (game->mouse_enabled)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	}
}

void	close_callback(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clean_exit(game);
	exit(0);
}
