/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:00:01 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*concatenate(int fd, char *raw_d)
{
	ssize_t	bytes_read;
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(raw_d, buffer);
		free(raw_d);
		if (temp == NULL)
			return (NULL);
		raw_d = temp;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(raw_d);
		return (NULL);
	}
	return (raw_d);
}

char	*parser_map(const char *buf)
{
	int		fd;
	char	*raw_data;

	fd = open(buf, O_RDONLY);
	if (fd == -1)
		return (NULL);
	raw_data = (char *)malloc(sizeof(char) * 1);
	if (raw_data == NULL)
	{
		close(fd);
		return (NULL);
	}
	raw_data[0] = '\0';
	raw_data = concatenate(fd, raw_data);
	if (raw_data == NULL)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (raw_data);
}

char	*scanning_and_extraction(t_game *game, const char *arg)
{
	char		*parser_tex_color;
	const char	*err_msg_str;

	init_game(game);
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
	while (*cursor != '\0' && *cursor != '\n')
		cursor++;
	if (*cursor == '\n')
	{
		*cursor = '\0';
		return (cursor + 1);
	}
	return (cursor);
}

static int	check_parse(t_game *game, char **cursor, int *elements_found)
{
	if (ft_strncmp(*cursor, "NO ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_n) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "SO ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_s) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "WE ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_w) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "EA ", 3) == 0 && parse_texture(game, cursor,
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

int	parser_map_width(char *scout)
{
	int	current_width;
	int	map_width;

	if (scout == NULL || *scout == '\0')
		return (err_msg("width", ERROR_SIZE_MAP, -1));
	map_width = 0;
	current_width = 0;
	while (*scout != '\0')
	{
		if (*scout == '\n')
		{
			if (current_width > map_width)
				map_width = current_width;
			current_width = 0;
		}
		else
			current_width++;
		scout++;
	}
	if (current_width > map_width)
		map_width = current_width;
	return (map_width);
}

static int	process_height_char(char c, int *map_height, int *map_ended,
								int *line_len)
{
	if (c == '\n')
	{
		if (*line_len == 0 && *map_height > 0)
			*map_ended = 1;
		*line_len = 0;
		(*map_height)++;
	}
	else
	{
		if ((c == '1' || c == '0' || c == 'N' || c == 'W' || c == 'S'
				|| c == 'E') && *map_ended == 1)
			return (err_msg("height", ERROR_INCOMPLETE_MAP, -1));
		(*line_len)++;
	}
	return (0);
}

int	parser_map_height(char *scout)
{
	int	map_height;
	int	map_ended;
	int	line_len;

	if (scout == NULL || *scout == '\0')
		return (err_msg("height", ERROR_SIZE_MAP, -1));
	map_height = 0;
	map_ended = 0;
	line_len = 0;
	while (*scout != '\0')
	{
		if (process_height_char(*scout, &map_height, &map_ended,
				&line_len) == -1)
			return (-1);
		scout++;
	}
	if (*scout == '\0' && line_len > 0)
		map_height++;
	return (map_height);
}

t_u8	*map_measurement(char *map_start_cursor, t_game *game)
{
	char	*scout;
	int		map_width;
	int		map_height;

	while (*map_start_cursor == '\n')
		map_start_cursor++;
	scout = map_start_cursor;
	map_width = parser_map_width(scout);
	if (map_width == -1)
		return (NULL);
	game->map_width = map_width;
	map_height = parser_map_height(scout);
	if (map_height == -1)
		return (NULL);
	game->map_height = map_height;
	game->map = (uint8_t *)malloc(sizeof(uint8_t) * map_width * map_height);
	if (game->map == NULL)
		return (NULL);
	ft_memset(game->map, ' ', map_width * map_height);
	return (game->map);
}
