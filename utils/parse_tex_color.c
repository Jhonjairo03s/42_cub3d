/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 01:26:13 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/21 18:59:16 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		return (-1);
	return (0);
}

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
	*color = (rgb[0] << 24) | (rgb[1] << 16) | ( rgb[2] << 8) | 255;
	return (0);
}
