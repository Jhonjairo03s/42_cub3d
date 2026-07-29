/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:44:26 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:44:13 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Scans the raw file string to ensure all four directional texture
 *        identifiers (NO, SO, WE, EA) are present exactly once.
 *
 * @param map The raw file content string.
 * @return int 0 if all four identifiers are strictly unique, -1 if any is
 *         missing or duplicated.
 */
static int	validate_identifiers_textures(char *map)
{
	int	no;
	int	so;
	int	we;
	int	ea;

	no = 0;
	so = 0;
	we = 0;
	ea = 0;
	while (*map != '\0')
	{
		if (ft_strncmp(map, "NO ", 3) == 0)
			no++;
		else if (ft_strncmp(map, "SO ", 3) == 0)
			so++;
		else if (ft_strncmp(map, "WE ", 3) == 0)
			we++;
		else if (ft_strncmp(map, "EA ", 3) == 0)
			ea++;
		map++;
	}
	if (no != 1 || so != 1 || we != 1 || ea != 1)
		return (err_msg("Identifiers", ERROR_IDENTIFIERS, -1));
	return (0);
}

/**
 * @brief Scans the raw file string to ensure the Floor (F) and Ceiling (C)
 *        color identifiers are present exactly once.
 *
 * @param map The raw file content string.
 * @return int 0 if both identifiers are strictly unique, -1 if missing or 
 *	       duplicated.
 */
static int	validate_identifiers_colors(char *map)
{
	int	f;
	int	c;

	f = 0;
	c = 0;
	while (*map != '\0')
	{
		if (ft_strncmp(map, "F ", 2) == 0)
			f++;
		else if (ft_strncmp(map, "C ", 2) == 0)
			c++;
		map++;
	}
	if (f != 1 || c != 1)
		return (err_msg("Identifiers", ERROR_IDENTIFIERS, -1));
	return (0);
}

/**
 * @brief Identifies the current line's metadata type, triggers the corresponding
 *        extraction function, or skips valid whitespaces.
 *
 * @param game Pointer to the main game structure.
 * @param cursor Double pointer to the current reading position in the raw 
 *	      string.
 * @param elements_found Pointer to the counter of successfully extracted 
 *	      metadata.
 * @return int 0 on successful extraction or valid whitespace skip, -1 if
 *         garbage/invalid characters are detected.
 *
 * @note This is the strict gatekeeper. If it finds anything other than the 6
 *       valid identifiers or formatting spaces/newlines, it triggers an error.
 */
static int	check_parse(t_game *game, char **cursor, int *elements_found)
{
	if (ft_strncmp(*cursor, "NO ", 3) == 0 && parse_texture(cursor,
			&game->tex_n) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "SO ", 3) == 0 && parse_texture(cursor,
			&game->tex_s) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "WE ", 3) == 0 && parse_texture(cursor,
			&game->tex_w) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "EA ", 3) == 0 && parse_texture(cursor,
			&game->tex_e) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "F ", 2) == 0 && parse_color(cursor,
			&game->floor_color) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "C ", 2) == 0 && parse_color(cursor,
			&game->ceil_color) == 0)
		return ((*elements_found)++, 0);
	else if (**cursor == '\n' || **cursor == ' ' || **cursor == '\t')
		return ((*cursor)++, 0);
	else
		return (err_msg("Metadata", ERROR_METADATA, -1));
}

/**
 * @brief Main extraction loop for all textures and colors. Validates the counts,
 *        then processes the file string until all 6 configuration elements 
 *        are found.
 *
 * @param game Pointer to the main game structure.
 * @param map The raw file content string.
 * @return char* A pointer to the exact location in the string where the
 *         metadata ends and the map grid begins, or NULL on error.
 *
 * @note By returning the advanced cursor, we seamlessly hand off the string
 *       to the map topology functions without needing to re-read the file.
 */
char	*parse_path(t_game *game, char *map)
{
	char	*cursor;
	char	*cursor_tex;
	char	*cursor_color;
	int		elements_found;

	cursor = map;
	cursor_tex = map;
	cursor_color = map;
	elements_found = 0;
	if (validate_identifiers_textures(cursor_tex) == -1
		|| validate_identifiers_colors(cursor_color) == -1)
		return (NULL);
	while (*cursor != '\0' && elements_found < 6)
	{
		if (check_parse(game, &cursor, &elements_found) == -1)
			return (NULL);
		if (*cursor == '\n' || (*cursor != '\0' && elements_found < 6))
			continue ;
	}
	if (elements_found != 6)
		return (NULL);
	return (cursor);
}
