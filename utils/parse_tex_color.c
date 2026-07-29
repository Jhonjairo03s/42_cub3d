/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 01:26:13 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:37:39 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Advances the cursor to the end of the current line and isolates it.
 *
 * @param cursor Pointer to the string to be terminated.
 * @return char* Pointer to the beginning of the next line.
 *
 * @note This uses a zero-allocation trick: it modifies the raw string in place
 *       by replacing the newline character ('\n') with a null terminator ('\0').
 *       This allows standard C functions to read the isolated line as a
 *       standalone string without needing malloc/ft_substr.
 */
char	*master_cursor(char *cursor)
{
	while (*cursor != '\0' && *cursor != '\n')
		cursor++;
	if (*cursor == '\n')
	{
		*cursor = '\0';
		return (cursor + 1);
	}
	return (cursor);
}

/*
int	parse_texture(t_game *game, char **cursor, t_u32 **tex, void **img)
{
	char	*path_start;

	*cursor = *cursor + 3;
	while (**cursor == ' ')
		(*cursor)++;
	path_start = *cursor;
	*cursor = master_cursor(path_start);
	*tex = load_texture(game, path_start, img);
	if (*tex == NULL)
		return (err_msg("Texture", ERROR_TEXTURE, -1));
	return (0);
}
*/

/**
 * @brief Extracts the file path of a texture and loads it via MLX42.
 *
 * @param cursor Double pointer to the current reading position 
 *        (at the identifier).
 * @param tex Double pointer to the MLX texture struct where the image will be 
 *        stored.
 * @return int 0 if the texture is successfully loaded, -1 on failure.
 *
 * @note It skips the 3-character identifier (e.g., "NO ") and any trailing 
 *       spaces, then uses master_cursor to isolate the path string before 
 *       passing it to the agnostic texture loader.
 */
int	parse_texture(char **cursor, mlx_texture_t **tex)
{
	char	*path_start;

	*cursor = *cursor + 3;
	while (**cursor == ' ')
		(*cursor)++;
	path_start = *cursor;
	*cursor = master_cursor(path_start);
	*tex = load_texture_agnostic(path_start);
	if (*tex == NULL)
		return (err_msg("Texture", ERROR_TEXTURE, -1));
	return (0);
}

/**
 * @brief Helper function to skip spaces and extract a single RGB integer.
 *
 * @param cursor Double pointer to the string containing the numbers.
 * @return int The extracted integer, or -1 if the parsing fails.
 */
static int	get_color(char **cursor)
{
	int	rgb;

	while (**cursor == ' ')
		(*cursor)++;
	rgb = ft_atoi_rgb(cursor);
	if (rgb == -1)
		return (-1);
	return (rgb);
}

/**
 * @brief Parses an RGB string (e.g., "255, 0, 0"), validates it, and packs it
 *        into a 32-bit unsigned integer (RGBA format for MLX42).
 *
 * @param cursor Double pointer to the string starting at the color identifier.
 * @param color Pointer to the t_u32 variable where the packed color will be 
 *	      stored.
 * @return int 0 on success, -1 if format, range, or syntax is invalid.
 *
 * @note Uses bitwise left shifts (<<) to pack the Red, Green, and Blue channels
 *       into their respective bytes. A hardcoded 255 (0xFF) is placed in the
 *       lowest byte as the Alpha (opacity) channel, since Cub3D does not use 
 *       transparency.
 */
int	parse_color(char **cursor, t_u32 *color)
{
	int	rgb[3];
	int	index;

	*cursor = *cursor + 2;
	index = 0;
	while (index < 3)
	{
		rgb[index] = get_color(cursor);
		if (rgb[index] == -1)
			return (err_msg("RGB", ERROR_RGB, -1));
		if (rgb[index] < 0 || rgb[index] > 255)
			return (err_msg("Range", ERROR_RANGE_RGB, -1));
		if (index < 2 && **cursor != ',')
			return (err_msg("Commas", ERROR_COMMAS, -1));
		if (index < 2)
			(*cursor)++;
		index++;
	}
	*color = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 255;
	return (0);
}
