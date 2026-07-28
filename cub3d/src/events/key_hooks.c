/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 15:25:00 by jhvalenc         ###   ########.fr       */
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

void	close_callback(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clean_exit(game);
	exit(0);
}
