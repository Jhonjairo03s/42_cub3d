/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/20 19:40:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	char	*parser_tex_and_color;
	t_u8	*size_map;

	if (program_validation(argc, argv[1]) == -1)
		return (1);
	game = (t_game *)malloc(sizeof(t_game));
	if (game == NULL)
		return (1);
	parser_tex_and_color = scanning_and_extraction(game, argv[1]);
	if (parser_tex_and_color == NULL)
		return (1);
	size_map = topology_and_map_memory(game, parser_tex_and_color);
	if (size_map == NULL)
		return (1);
	if (iteractive_flood_fill(game) == -1)
	{
		clean_exit(game);
		return (1);
	}
	debug_print_final_struct(game);
	//free(game->raw_data);
	clean_exit(game);
	//free(size_map);
	//free(game);
	return (0);
}
