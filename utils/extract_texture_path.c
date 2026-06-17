/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:44:26 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/10 19:35:21 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

static int	check_parse(t_game *game, char **cursor, int *elements_found)
{
	if (ft_strncmp(*cursor, "NO ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_n, &game->img_n) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "SO ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_s, &game->img_s) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "WE ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_w, &game->img_w) == 0)
		return ((*elements_found)++, 0);
	else if (ft_strncmp(*cursor, "EA ", 3) == 0 && parse_texture(game, cursor,
			&game->tex_e, &game->img_e) == 0)
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

/*
static int	check_parse(t_game *game, char **cursor, int *elements_found)
{
	int	res;

	if (ft_strncmp(*cursor, "NO ", 3) == 0)
	{
		res = parse_texture(game, cursor, &game->tex_n, &game->img_n);
		if (res == -1)
			return (err_msg("Textura", "Error al cargar textura NO", -1));
		return ((*elements_found)++, 0);
	}
	if (ft_strncmp(*cursor, "SO ", 3) == 0)
	{
		res = parse_texture(game, cursor, &game->tex_s, &game->img_s);
		if (res == -1)
			return (err_msg("Textura", "Error al cargar textura SO", -1));
		return ((*elements_found)++, 0);
	}
	if (ft_strncmp(*cursor, "WE ", 3) == 0)
	{
		res = parse_texture(game, cursor, &game->tex_w, &game->img_w);
		if (res == -1)
			return (err_msg("Textura", "Error al cargar textura WE", -1));
		return ((*elements_found)++, 0);
	}
	if (ft_strncmp(*cursor, "EA ", 3) == 0)
	{
		res = parse_texture(game, cursor, &game->tex_e, &game->img_e);
		if (res == -1)
			return (err_msg("Textura", "Error al cargar textura EA", -1));
		return ((*elements_found)++, 0);
	}
	if (ft_strncmp(*cursor, "F ", 2) == 0)
	{
		if (parse_color(cursor, &game->floor_color) == -1)
			return (err_msg("Color", "Formato de color F invalido", -1));
		return ((*elements_found)++, 0);
	}
	if (ft_strncmp(*cursor, "C ", 2) == 0)
	{
		if (parse_color(cursor, &game->ceil_color) == -1)
			return (err_msg("Color", "Formato de color C invalido", -1));
		return ((*elements_found)++, 0);
	}
	if (**cursor == '\n')
	{
		(*cursor)++;
		return (0);
	}
	return (err_msg("Parser", "Caracter o elemento invalido en metadatos", -1));
}
*/
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
