/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/27 19:28:27 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	char	*parser_tex_and_color;

	if (program_validation(argc, argv[1]) == -1)
		return (1);
	game = (t_game *)malloc(sizeof(t_game));
	if (game == NULL)
		return (1);
	parser_tex_and_color = scanning_and_extraction(game, argv[1]);
	if (parser_tex_and_color == NULL)
		return (clean_exit(game), 1);
	if (topology_and_map_memory(game, parser_tex_and_color) == -1)
		return (clean_exit(game), 1);
	if (check_global_closure(game) == -1)
		return (clean_exit(game), 1);
	if (iteractive_flood_fill(game) == -1)
		return (clean_exit(game), 1);
	debug_print_final_struct(game);
	clean_exit(game);
	return (0);
}
