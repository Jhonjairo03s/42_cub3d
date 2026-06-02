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

/*
char	*explore_map(char *map, const char *prefix)
{
	char	*cursor;
	int		found;

	cursor = map;
	found = 0;
	while (*cursor != '\0')
	{
		if (*cursor == prefix[0] && *(cursor + 1) == prefix[1] && *(cursor + 2) == ' ')
			found = 1;
		if (found == 1)
		{
			cursor = cursor + 3;
			while (*cursor == ' ')
				cursor++;
			if (*cursor != '\0' && *cursor != '\n')
				return (cursor);
		}
		cursor++;
	}
	return (NULL);
}

char	*extract_texture_path(char *extraction)
{
	char	*ptr_text;
	char	*start_ptr;

	ptr_text = extraction;
	start_ptr = ptr_text;
	while (*ptr_text != '\0')
	{
		if (*ptr_text == '\0')
			return (start_ptr);
		if (*ptr_text == '\n')
		{
			*ptr_text = '\0';
			return (start_ptr);
		}
		ptr_text++;
	}
	return (NULL);
}
*/

char	*master_cursor(char *cursor)
{
	while (*cursor != '\0' && *cursor != '\n')
		cursor++;
	if (*cursor == '\n')
		*cursor = '\0';
	return (cursor);
}

char	*parse_path(t_game *game, char *map)
{
	char	*cursor;
	char	*path_start;
	int		elements_found;
	int		r;
	int		g;
	int		b;

	cursor = map;
	elements_found = 0;
	while (*cursor != '\0' && elements_found < 6)
	{
		if (*cursor == 'N' && *(cursor + 1) == 'O' && *(cursor + 2) == ' ')
		{
			cursor = cursor + 3;
			while (*cursor == ' ')
				cursor++;
			path_start = cursor;
			cursor = master_cursor(cursor);
			//game->tex_n = funcion_que_aun_no_existe(game->mlx_ptr, path_start);
			elements_found++;
		}
		else if (*cursor == 'S' && *(cursor + 1) == 'O' && *(cursor + 2) == ' ')
		{
			cursor = cursor + 3;
			while (*cursor == ' ')
				cursor++;
			path_start = cursor;
			cursor = master_cursor(cursor);
			//game->tex_s = funcion_que_aun_no_existe(game->mlx_ptr, path_start);
			elements_found++;
		}
		else if (*cursor == 'W' && *(cursor + 1) == 'E' && *(cursor + 2) == ' ')
		{
			cursor = cursor + 3;
			while (*cursor == ' ')
				cursor++;
			path_start = cursor;
			cursor = master_cursor(cursor);
			//game->tex_w = funcion_que_aun_no_existe(game->mlx_ptr, path_start);
			elements_found++;
		}
		else if (*cursor == 'E' && *(cursor + 1) == 'A' && *(cursor + 2) == ' ')
		{
			cursor = cursor + 3;
			while (*cursor == ' ')
				cursor++;
			path_start = cursor;
			cursor = master_cursor(cursor);
			//game->tex_e = funcion_que_aun_no_existe(game->mlx_ptr, path_start);
			elements_found++;
		}
		else if (*cursor == 'F' && *(cursor + 1) == ' ')
		{
			cursor = cursor + 2;
			while (*cursor == ' ')
				cursor++;
			while (*cursor != '\0')
			{
				if ((*cursor >= '0' && *cursor <= '9') || (*(cursor + 1) >= '0' && *(cursor + 1) <= '9'))
				{
					r = ft_atoi_rgb(&cursor);
					if (r < 0 || r > 255)
						return (NULL);
					else
						cursor++;
					g = ft_atoi_rgb(&cursor);
					if (g < 0 || g > 255)
						return (NULL);
					else
						cursor++;
					b = ft_atoi_rgb(&cursor);
					if (b < 0 || b > 255)
						return (NULL);
					else
						cursor++;
				}
			}
		}
		else if (*cursor == 'C' && *(cursor + 1) == ' ')
		{
			cursor = cursor + 2;
			while (*cursor == ' ')
				cursor++;
			while (*cursor != '\0')
			{
				if ((*cursor >= '0' && *cursor <= '9') || (*(cursor + 1) >= '0' && *(cursor + 1) <= '9'))
				{
					r = ft_atoi_rgb(&cursor);
					if (r < 0 || r > 255)
						return (NULL);
					else
						cursor++;
					g = ft_atoi_rgb(&cursor);
					if (g < 0 || g > 255)
						return (NULL);
					else
						cursor++;
					b = ft_atoi_rgb(&cursor);
					if (b < 0 || b > 255)
						return (NULL);
					else
						cursor++;
				}
			}
		}
		cursor++;
	}
	if (elements_found != 6)
		return (NULL);
	// cuando llame a la función debo de lanzar mensaje de ERROR
	// si retorna NULL
	return (cursor);
}
