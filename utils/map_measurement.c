/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_measurement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:33:34 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/17 11:19:53 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parser_map_width(char *scout)
{
	int	current_width;
	int	map_width;

	if (scout == NULL || *scout == '\0')
		return (-1);
	map_width = 0;
	current_width = 0;
	while (*scout != '\0')
	{
		if (*scout == '\n')
		{
			if (current_width > map_width)
				map_width = current_width;
			current_width = 0;
		}
		else
			current_width++;
		scout++;
	}
	if (current_width > map_width)
		map_width = current_width;
	return (map_width);
}

int	parser_map_height(char *scout)
{
	int	map_height;
	int	map_ended;
	int	line_len;

	if (scout == NULL || *scout == '\0')
		return (-1);
	map_height = 0;
	map_ended = 0;
	line_len = 0;
	while (*scout != '\0')
	{
		if (*scout == '\n')
		{
			if (line_len == 0 && map_height > 0)
				map_ended = 1;
			line_len = 0;
			map_height++;
		}
		else
		{
			if ((*scout == '1' || *scout == '0' || *scout == 'N'
					|| *scout == 'W' || *scout == 'E'
					|| *scout == 'S') && map_ended == 1)
				return (-1);
			line_len++;
		}
		scout++;
	}
	if (*scout == '\0' && line_len > 0)
		map_height++;
	return (map_height);
}

t_u8	*map_measurement(char *map_start_cursor, t_game *game)
{
	char	*scout;
	int		map_width;
	int		map_height;

	scout = map_start_cursor;
	map_width = parser_map_width(scout);
	if (map_width == -1)
		return (NULL);
	game->map_width = map_width;
	map_height = parser_map_height(scout);
	if (map_height == -1)
		return (NULL);
	game->map_height = map_height;
	game->map = (uint8_t *)malloc(sizeof(uint8_t) * map_width * map_height);
	if (game->map == NULL)
		return (NULL);
	ft_memset(game->map, ' ', map_width * map_height);
	return (game->map);
}
