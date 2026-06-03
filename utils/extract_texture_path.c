/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:44:26 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 17:47:31 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*master_cursor(char *cursor)
{
	while (*cursor != '\0' && *cursor != '\n')
		cursor++;
	if (*cursor == '\n')
		*cursor = '\0';
	return (cursor);
}

static int	parse_color(t_u32 *color, char **cursor)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi_rgb(cursor);
	if (**cursor != ',')
		return (1);
	(*cursor)++;
	g = ft_atoi_rgb(cursor);
	if (**cursor != ',')
		return (1);
	(*cursor)++;
	b = ft_atoi_rgb(cursor);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	*color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (0);
}

static char	*skip_and_find(char *cursor, const char *id, int *elements)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(cursor, id, len) == 0 && cursor[len] == ' ')
	{
		cursor += len;
		while (*cursor == ' ')
			cursor++;
		(*elements)++;
		return (cursor);
	}
	return (NULL);
}

static char	*parse_element(t_game *game, char *cursor, int *elements)
{
	char	*path;

	path = skip_and_find(cursor, "NO", elements);
	if (path && (cursor = master_cursor(path)))
		return (cursor);
	path = skip_and_find(cursor, "SO", elements);
	if (path && (cursor = master_cursor(path)))
		return (cursor);
	path = skip_and_find(cursor, "WE", elements);
	if (path && (cursor = master_cursor(path)))
		return (cursor);
	path = skip_and_find(cursor, "EA", elements);
	if (path && (cursor = master_cursor(path)))
		return (cursor);
	path = skip_and_find(cursor, "F", elements);
	if (path && parse_color(&game->floor_color, &path) == 0)
		return (master_cursor(path));
	path = skip_and_find(cursor, "C", elements);
	if (path && parse_color(&game->ceil_color, &path) == 0)
		return (master_cursor(path));
	return (NULL);
}

char	*parse_path(t_game *game, char *map)
{
	char	*cursor;
	char	*next;
	int		elements;

	cursor = map;
	elements = 0;
	while (*cursor != '\0' && elements < 6)
	{
		while (*cursor == ' ' || *cursor == '\n')
			cursor++;
		if (*cursor == '\0')
			break ;
		next = parse_element(game, cursor, &elements);
		if (next)
			cursor = next + 1;
		else
			cursor++;
	}
	if (elements != 6)
		return (NULL);
	return (cursor);
}
