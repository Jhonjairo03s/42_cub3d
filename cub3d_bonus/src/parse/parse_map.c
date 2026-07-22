/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:00:01 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:07:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*scanning_and_extraction(t_game *game, const char *arg)
{
	char		*parser_tex_color;
	const char	*err_msg_str;

	err_msg_str = "file - loading file\n";
	game->raw_data = parser_map(arg);
	if (game->raw_data == NULL)
	{
		write(STDERR_FILENO, "Error\n", 6);
		write(STDERR_FILENO, err_msg_str, ft_strlen(err_msg_str));
		return (NULL);
	}
	parser_tex_color = parse_path(game, game->raw_data);
	if (parser_tex_color == NULL)
		return (NULL);
	return (parser_tex_color);
}

char	*master_cursor(char *cursor)
{
	char	*line_end;

	line_end = cursor;
	while (*line_end != '\0' && *line_end != '\n')
		line_end++;
	if (*line_end == '\n')
	{
		*line_end = '\0';
		line_end++;
	}
	while (line_end > cursor && (*(line_end - 1) == '\r'
			|| *(line_end - 1) == ' ' || *(line_end - 1) == '\t'))
	{
		line_end--;
		*line_end = '\0';
	}
	return (cursor + ft_strlen(cursor) + 1);
}

static int	parse_tex_helper(t_game *game, char **cursor, int *found)
{
	if (ft_strncmp(*cursor, "NO ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_n) == 0 && ++(*found))
		return (1);
	if (ft_strncmp(*cursor, "SO ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_s) == 0 && ++(*found))
		return (1);
	if (ft_strncmp(*cursor, "WE ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_w) == 0 && ++(*found))
		return (1);
	if (ft_strncmp(*cursor, "EA ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_e) == 0 && ++(*found))
		return (1);
	return (0);
}

static int	check_parse(t_game *game, char **cursor, int *elements_found)
{
	if (parse_tex_helper(game, cursor, elements_found))
		return (0);
	if (ft_strncmp(*cursor, "F ", 2) == 0 && parse_color(cursor,
			&game->floor_color) == 0 && ++(*elements_found))
		return (0);
	if (ft_strncmp(*cursor, "C ", 2) == 0 && parse_color(cursor,
			&game->ceil_color) == 0 && ++(*elements_found))
		return (0);
	if (**cursor == '\n' || **cursor == '\r')
	{
		(*cursor)++;
		return (0);
	}
	return (-1);
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
		if (*cursor != '\0' && elements_found < 6)
			continue ;
	}
	if (elements_found != 6)
		return (NULL);
	return (cursor);
}
