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
	t_game		*game;
	long long	current_time;
	long long	elapsed;

	game = (t_game *)param;
	current_time = get_time_in_ms();
	elapsed = current_time - game->time_data.last_time;
	if (elapsed == 0)
		return ;
	game->time_data.last_time = current_time;
	game->time_data.anim_timer += elapsed;
	if (game->time_data.anim_timer >= 150)
	{
		game->time_data.sprite_frame = (game->time_data.sprite_frame + 1) % 4;
		game->time_data.anim_timer = 0;
	}
	update_player(game, elapsed);
	update_enemy(game, elapsed);
	render(game);
	draw_fps(game);
}

static int	init_graphics(t_game *game)
{
	int32_t	dummy_y;

	if (!game->mlx)
		return (err_msg("MLX init", ERROR_FD_OPEN, 1));
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		mlx_terminate(game->mlx);
		return (err_msg("Image creation", ERROR_FD_OPEN, 1));
	}
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(game->mlx, &game->prev_mouse_x, &dummy_y);
	return (0);
}

static void	start_game(t_game *game)
{
	game_loop(game);
	mlx_key_hook(game->mlx, key_cb, game);
	mlx_cursor_hook(game->mlx, mouse_cb, game);
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
	if (game.z_buffer)
		free(game.z_buffer);
	mlx_terminate(game.mlx);
	return (0);
}
