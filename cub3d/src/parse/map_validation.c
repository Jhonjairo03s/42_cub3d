/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:00:01 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 16:02:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*scanning_and_extraction(t_game *game, const char *arg)
{
	char	*parser_tex_color;

	init_game(game);
	game->raw_data = parser_map(arg);
	if (game->raw_data == NULL)
	{
		err_msg("file", "loading file\n", 0);
		return (NULL);
	}
	parser_tex_color = parse_path(game, game->raw_data);
	if (parser_tex_color == NULL)
		return (NULL);
	return (parser_tex_color);
}

t_i32	topology_and_map_memory(t_game *game, char *parser_tex_color)
{
	t_i32	player;

	if (map_measurement(parser_tex_color, game) == NULL)
		return (-1);
	if (dump_and_fill(parser_tex_color, game) == NULL)
		return (-1);
	player = init_player(game);
	if (player != 0)
		return (-1);
	return (0);
}

static t_i32	is_open_space(t_game *game, t_i32 x, t_i32 y)
{
	t_i32	index;

	if (x == 0 || x == game->map_width - 1 || y == 0
		|| y == game->map_height - 1)
		return (1);
	index = y * game->map_width + x;
	if (game->map[index - 1] == ' ' || game->map[index + 1] == ' '
		|| game->map[index - game->map_width] == ' '
		|| game->map[index + game->map_width] == ' ')
		return (1);
	return (0);
}

t_i32	check_global_closure(t_game *game)
{
	t_i32	x;
	t_i32	y;
	t_i32	index;
	t_u8	c;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			index = y * game->map_width + x;
			c = game->map[index];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (is_open_space(game, x, y) == 1)
					return (err_msg("Map limit", ERROR_LIMIT_FF, -1));
			}
			x++;
		}
		y++;
	}
	return (0);
}
