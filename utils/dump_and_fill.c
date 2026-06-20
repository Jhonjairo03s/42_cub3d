/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:23:30 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/20 19:14:02 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_u8	*dump_machine(char *src, t_game *game)
{
	int	index;
	int	x;
	int	y;

	index = 0;
	x = 0;
	y = 0;
	while (*src != '\0' && y < game->map_height)
	{
		if (*src == '1' || *src == '0' || *src == 'N' || *src == 'S'
			|| *src == 'E' || *src == 'W' || *src == ' ' || *src == '\t')
		{
			index = (y * game->map_width) + x;
			game->map[index] = *src;
			x++;
		}
		if (*src == '\n')
		{
			y++;
			x = 0;
		}
		src++;
	}
	return (game->map);
}

t_u8	*dump_and_fill(char *cursor, t_game *game)
{
	char	*src;
	t_u8	*map_fill;

	src = cursor;
	while (*src == '\n')
		src++;
	map_fill = dump_machine(src, game);
	return (map_fill);
}
