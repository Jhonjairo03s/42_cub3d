/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_measurement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:33:34 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:38:49 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Calculates the maximum width of the map grid.
 *
 * @param scout Pointer to the start of the map section in the raw string.
 * @return int The length of the longest line in the map, or -1 on error.
 *
 * @note Because Cub3D maps can be irregular (jagged edges), this function
 *       finds the absolute maximum X dimension to define the width of our
 *       rectangular 1D array bounding box.
 */
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

/**
 * @brief Helper function to process individual characters during height 
 *	      calculation and detect fractured maps 
 *	      (empty lines inside the map body).
 *
 * @param c The current character being evaluated.
 * @param map_height Pointer to the total height counter.
 * @param map_ended Pointer to a flag 
 *	      (1 if an empty line was found after map start).
 * @param line_len Pointer to the length of the current line.
 * @return int 0 on success, -1 if a fractured map is detected.
 */
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
				|| c == 'E') && *map_ended == 1)
			return (err_msg("height", ERROR_INCOMPLETE_MAP, -1));
		(*line_len)++;
	}
	return (0);
}

/**
 * @brief Calculates the total height (number of rows) of the map grid and
 *        ensures the map is a single contiguous block.
 *
 * @param scout Pointer to the start of the map section in the raw string.
 * @return int The total number of rows, or -1 on error (e.g., fractured map).
 */
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

/**
 * @brief Measures the map bounds and allocates the linear 1D memory grid.
 *
 * @param map_start_cursor Pointer to the raw string where metadata ends.
 * @param game Pointer to the main game structure.
 * @return t_u8* A pointer to the newly allocated and initialized 1D map array,
 *         or NULL on failure.
 *
 * @note The allocated memory is immediately flooded with spaces (' ') using
 *       ft_memset. This is a crucial architectural decision: it ensures that
 *       any "empty" areas caused by jagged map edges are automatically padded
 *       with secure void characters instead of uninitialized memory.
 */
t_u8	*map_measurement(char *map_start_cursor, t_game *game)
{
	char	*scout;
	int		map_width;
	int		map_height;

	while (*map_start_cursor == '\n')
		map_start_cursor++;
	scout = map_start_cursor;
	if (*scout != '1' && *scout != ' ')
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
