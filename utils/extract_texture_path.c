/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:44:26 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/05 01:35:06 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_parse(t_game *game, char **cursor, int *elements_found)
{
	if (ft_strncmp(*cursor, "NO ", 3) == 0 && parse_texture(game, *cursor,
			&game->tex_n, &game->img_n) != -1)
		return ((*elements_found)++, -1);
	else if (ft_strncmp(*cursor, "SO ", 3) == 0 && parse_texture(game, *cursor,
			&game->tex_s, &game->img_s) != -1)
		return ((*elements_found)++, -1);
	else if (ft_strncmp(*cursor, "WE ", 3) == 0 && parse_texture(game, *cursor,
			&game->tex_w, &game->img_w) != -1)
		return ((*elements_found)++, -1);
	else if (ft_strncmp(*cursor, "EA ", 3) == 0 && parse_texture(game, *cursor,
			&game->tex_e, &game->img_e) != -1)
		return ((*elements_found)++, -1);
	else if (ft_strncmp(*cursor, "F ", 2) == 0 && parse_color(cursor,
			&game->floor_color) != -1)
		return ((*elements_found)++, -1);
	else if (ft_strncmp(*cursor, "C ", 2) == 0 && parse_color(cursor,
			&game->ceil_color) != -1)
		return ((*elements_found)++, -1);
	return (0);
}

char	*parse_path(t_game *game, char *map)
{
	char	*cursor;
	int		elements_found;

	cursor = map;
	elements_found = 0;
	while (*cursor != '\0' && elements_found < 6)
	{
		if (check_parse(game, &cursor, &elements_found) == -1)
			return (NULL);
		if (*cursor != '\0' && *cursor != '\n')
			cursor++;
	}
	if (elements_found != 6)
		return (NULL);
	return (cursor);
}
