/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_measurement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:33:34 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/24 00:57:01 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int	parser_map_width(char *scout)
{
	int	current_width;
	int	map_width;

	if (scout == NULL || *scout == '\0')
		return (err_msg("width", ERROR_SIZE_MAP, -1));
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

static int	process_height_char(char c, int *map_height, int *map_ended,
								int *line_len)
{
	if (c == '\n')
	{
		if (*line_len == 0 && *map_height > 0)
			*map_ended = 1;
		*line_len = 0;
		(*map_height)++;
	}
	else
	{
		if ((c == '1' || c == '0' || c == 'N' || c == 'W' || c == 'S'
				|| c == 'N') && *map_ended == 1)
			return (err_msg("height", ERROR_INCOMPLETE_MAP, -1));
		(*line_len)++;
	}
	return (0);
}

int	parser_map_height(char *scout)
{
	int	map_height;
	int	map_ended;
	int	line_len;

	if (scout == NULL || *scout == '\0')
		return (err_msg("height", ERROR_SIZE_MAP, -1));
	map_height = 0;
	map_ended = 0;
	line_len = 0;
	while (*scout != '\0')
	{
		if (process_height_char(*scout, &map_height, &map_ended,
				&line_len) == -1)
			return (-1);
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

	while (*map_start_cursor == '\n' || *map_start_cursor == ' '
		|| *map_start_cursor == '\t')
		map_start_cursor++;
	scout = map_start_cursor;
	printf("-> %c\n", *scout);
	if (*scout != '1')
		return (err_msg("Character", ERROR_INIT_MAP, -1), NULL);
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
