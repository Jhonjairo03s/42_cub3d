/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:23:30 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/27 17:58:01 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_u8	*dump_machine(char *src, t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (*src != '\0' && y < game->map_height)
	{
		if (*src == '1' || *src == '0' || *src == 'N' || *src == 'S'
			|| *src == 'E' || *src == 'W' || *src == ' ')
		{
			game->map[(y * game->map_width) + x] = *src;
			x++;
		}
		else if (*src == '\n')
		{
			y++;
			x = 0;
		}
		else
			return (NULL);
		src++;
	}
	return (game->map);
}

t_u8	*dump_and_fill(char *cursor, t_game *game)
{
	char	*src;
	char	*err_msg;
	t_u8	*map_fill;

	src = cursor;
	while (*src == '\n')
		src++;
	err_msg = "Map content - Invalid character found on the map\n";
	map_fill = dump_machine(src, game);
	if (map_fill == NULL)
	{
		write(STDERR_FILENO, "Error\n", 6);
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
		return (NULL);
	}
	return (map_fill);
}
