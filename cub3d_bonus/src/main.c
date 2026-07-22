/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	game_loop(t_game *game)
{
	int64_t	current_time;
	int64_t	elapsed;

	current_time = get_time_in_ms();
	if (game->time_data.last_time == 0)
		game->time_data.last_time = current_time;
	elapsed = current_time - game->time_data.last_time;
	game->time_data.last_time = current_time;
	game->time_data.delta_time = elapsed / 1000.0;
	update_player(game, game->time_data.delta_time);
	render(game);
	if (game->frame.img_ptr && game->win_ptr && game->mlx_ptr)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->frame.img_ptr, 0, 0);
	return (0);
}

static void	start_game(t_game *game)
{
	mlx_hook(game->win_ptr, 2, (1L << 0),
		(int (*)())(void *)key_press_hook, game);
	mlx_hook(game->win_ptr, 3, (1L << 1),
		(int (*)())(void *)key_release_hook, game);
	mlx_hook(game->win_ptr, 17, 0,
		(int (*)())(void *)close_hook, game);
	mlx_loop_hook(game->mlx_ptr, (int (*)())(void *)game_loop, game);
	mlx_loop(game->mlx_ptr);
}

static int	setup_map(t_game *game, char *arg)
{
	char	*parser_tex_and_color;

	init_game(game);
	parser_tex_and_color = scanning_and_extraction(game, arg);
	if (parser_tex_and_color == NULL)
		return (-1);
	if (topology_and_map_memory(game, parser_tex_and_color) == -1)
		return (-1);
	if (iteractive_flood_fill(game) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (program_validation(argc, argv[1]) == -1)
		return (1);
	game = (t_game *)malloc(sizeof(t_game));
	if (game == NULL)
		return (1);
	if (setup_map(game, argv[1]) == -1 || init_graphics(game) != 0)
	{
		clean_exit(game);
		return (1);
	}
	start_game(game);
	clean_exit(game);
	return (0);
}
