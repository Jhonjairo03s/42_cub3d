/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 12:20:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "mlx/include/MLX42/MLX42.h"

static void	key_cb(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_F3 && keydata.action == MLX_PRESS)
		game->show_fps = !game->show_fps;
}

static void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_player(game);
	render(game);
	draw_fps(game);
}

static int	init_graphics(t_game *game)
{
	if (!game->mlx)
		return (err_msg("MLX init", ERROR_FD_OPEN, 1));
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		mlx_terminate(game->mlx);
		return (err_msg("Image creation", ERROR_FD_OPEN, 1));
	}
	return (0);
}

static void	start_game(t_game *game)
{
	game_loop(game);
	mlx_key_hook(game->mlx, key_cb, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
		return (err_msg("Usage", ERROR_USAGE, 1));
	if (program_validation(argv[1]) != 0)
		return (1);
	init_game(&game);
	if (init_graphics(&game) != 0)
		return (1);
	start_game(&game);
	if (game.fps_img)
		mlx_delete_image(game.mlx, game.fps_img);
	mlx_terminate(game.mlx);
	return (0);
}
