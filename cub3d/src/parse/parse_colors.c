/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 01:26:13 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_atoi_rgb(char **str)
{
	int	result;
	int	digits;

	result = 0;
	digits = 0;
	while (**str == ' ')
		(*str)++;
	if (**str == '-' || **str == '+')
		return (-1);
	while (**str >= '0' && **str <= '9')
	{
		result = (result * 10) + (**str - '0');
		(*str)++;
		digits++;
	}
	if (digits == 0)
		return (-1);
	while (**str == ' ')
		(*str)++;
	if (**str != ',' && **str != '\n' && **str != '\0')
		return (-1);
	return (result);
}

int	parse_texture(t_game *game, char **cursor, t_img **tex)
{
	char	*path_start;

	*cursor = *cursor + 3;
	while (**cursor == ' ')
		(*cursor)++;
	path_start = *cursor;
	*cursor = master_cursor(path_start);
	*tex = load_texture(game->mlx_ptr, path_start);
	if (*tex == NULL)
		return (err_msg("Texture", ERROR_TEXTURE, -1));
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
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (0);
}
