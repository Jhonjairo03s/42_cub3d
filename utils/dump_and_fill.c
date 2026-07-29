/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:23:30 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:06:15 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Core engine that transfers map characters from the raw string into
 *        the properly allocated 1D memory grid.
 *
 * @param src Pointer to the start of the actual map data in the raw string.
 * @param game Pointer to the main game structure containing the allocated map.
 * @return t_u8* Pointer to the populated map array, or NULL if any invalid
 *         character (including tabs or garbage) is detected.
 *
 * @note This function translates 2D coordinates (x, y) into a 1D index using
 *       the formula `(y * map_width) + x`. It acts as a strict filter, instantly
 *       aborting if any character outside the allowed subset is encountered.
 */
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

/**
 * @brief Prepares the cursor and handles the map transfer process.
 *
 * @param cursor Pointer to the raw string right after the metadata section.
 * @param game Pointer to the main game structure.
 * @return t_u8* Pointer to the fully populated map array, or NULL on error.
 *
 * @note It safely skips any empty lines separating the metadata from the map
 *       before feeding the clean string pointer to the dump_machine. If the
 *       machine fails, this function handles the specific error output.
 */
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
