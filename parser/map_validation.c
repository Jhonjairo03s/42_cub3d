/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:00:01 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:44:55 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Orchestrates the initialization, file reading, and metadata extraction.
 *
 * @param game Pointer to the main game structure.
 * @param arg  Path to the .cub file.
 * @return char* Pointer to the exact position in the raw string where the
 *         metadata ends and the map grid begins. Returns NULL on failure.
 *
 * @note This function loads the entire file into RAM (game->raw_data) and
 *       delegates the extraction of textures and colors to parse_path().
 */
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

/**
 * @brief Manages the memory allocation and population of the 1D map grid.
 *
 * @param game Pointer to the main game structure.
 * @param parser_tex_color Pointer to the start of the map grid in the raw 
 *	      string.
 * @return int 0 on success, -1 if memory allocation, dimension measurement,
 *         or player initialization fails.
 *
 * @note This function converts the irregular 2D map into a perfectly rectangular
 *       1D array, extracting the player's position and orientation vectors.
 */
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

/**
 * @brief Collision detection sensor. Checks if a walkable tile is exposed 
 *	      to the void.
 * 
 * @param game Pointer to the main game structure.
 * @param x    The x coordinate of the tile to check.
 * @param y    The y coordinate of the tile to check.
 * @return int 1 if the tile touches the absolute edge of the map or an empty 
 *         space (' '). Returns 0 if it is safely surrounded by walls or floors.
 */
static int	is_open_space(t_game *game, int x, int y)
{
	int	index;

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

/**
 * @brief Global scanner that ensures the map is strictly closed by walls.
 * 
 * @param game Pointer to the main game structure.
 * @return int 0 if the map is completely sealed. Returns -1 if any walkable 
 *         surface (floor or player position) is exposed to the void.
 * 
 * @note This acts as an absolute safeguard against structural leaks that might 
 *       trick standard flood fill algorithms (e.g., hidden spaces inside walls).
 */
int	check_global_closure(t_game *game)
{
	int		x;
	int		y;
	int		index;
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
