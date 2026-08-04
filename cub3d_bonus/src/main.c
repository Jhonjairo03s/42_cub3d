/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/08/04 16:04:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game || !game->mlx)
		return ;
	handle_keys(game);
	handle_mouse(game);
	update_player(game, game->mlx->delta_time);
	render(game);
	draw_minimap(game);
	draw_fps(game);
}

static void	start_game(t_game *game)
{
	mlx_close_hook(game->mlx, close_callback, game);
	mlx_key_hook(game->mlx, key_callback, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

static t_i32	setup_map(t_game *game, char *arg)
{
	char	*parser_tex_and_color;

	parser_tex_and_color = scanning_and_extraction(game, arg);
	if (parser_tex_and_color == NULL)
		return (-1);
	if (topology_and_map_memory(game, parser_tex_and_color) == -1)
		return (-1);
	if (check_global_closure(game) == -1)
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
	init_game(game);
	if (setup_map(game, argv[1]) == -1 || init_graphics(game) != 0)
	{
		clean_exit(game);
		return (1);
	}
	start_game(game);
	clean_exit(game);
	return (0);
}
