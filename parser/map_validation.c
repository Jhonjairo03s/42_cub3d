/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:00:01 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/24 00:01:55 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*scanning_and_extraction(t_game *game, const char *arg)
{
	char		*parser_tex_color;
	const char	*err_msg;

	init_game(game);
	err_msg = "file - loading file\n";
	game->raw_data = parser_map(arg);
	if (game->raw_data == NULL)
	{
		write(STDERR_FILENO, "Error\n", 6);
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));	
		return (NULL);
	}
	parser_tex_color = parse_path(game, game->raw_data);
	if (parser_tex_color == NULL)
		return (NULL);
	return (parser_tex_color);
}

int	topology_and_map_memory(t_game *game, char *parser_tex_color)
{
	int		player;

	if (map_measurement(parser_tex_color, game) == NULL)
		return (-1);
	if (dump_and_fill(parser_tex_color, game) == NULL)
		return (-1);
	player = init_player(game);
	if (player != 0)
		return (-1);
	return (0);
}
