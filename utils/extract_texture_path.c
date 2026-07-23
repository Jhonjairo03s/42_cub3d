/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:44:26 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/24 00:04:48 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	else if (**cursor == '\n')
		return ((*cursor)++, 0);
	else
		return (-1);
}

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
	if (validate_identifiers_textures(cursor_tex) == -1 ||
		validate_identifiers_colors(cursor_color) == -1)
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
