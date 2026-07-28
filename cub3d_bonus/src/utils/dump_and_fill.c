/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:23:30 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:42:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_tab(t_game *game, int *x, int *y)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (*x < game->map_width && *y < game->map_height)
			game->map[*y * game->map_width + *x] = ' ';
		(*x)++;
		i++;
	}
}

static int	copy_map_char(char c, t_game *game, int *x, int *y)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ')
	{
		if (*x < game->map_width && *y < game->map_height)
			game->map[*y * game->map_width + *x] = c;
		(*x)++;
	}
	else if (c == '\t')
		fill_tab(game, x, y);
	else if (c == '\n')
	{
		(*y)++;
		*x = 0;
	}
	else
		return (-1);
	return (0);
}

static t_u8	*dump_machine(char *src, t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (*src != '\0' && y < game->map_height)
	{
		if (copy_map_char(*src, game, &x, &y) == -1)
			return (NULL);
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
	if (map_fill == NULL)
	{
		err_msg("Map content", "Invalid character found on the map\n", 0);
		return (NULL);
	}
	return (map_fill);
}
