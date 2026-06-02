/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   east_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 23:24:48 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/05/31 20:31:18 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*explore_map_east(char *map)
{
	char	*cursor;
	int		no_found;

	cursor = map;
	no_found = 0;
	while (*cursor != '\0')
	{
		if (*cursor == 'E' && *(cursor + 1) == 'A' && *(cursor + 2) == ' ')
			no_found = 1;
		if (no_found == 1)
		{
			cursor = cursor + 3;
			while (*cursor == ' ' )
				cursor++;
			if (*cursor != '\0' && *cursor != '\n')
				return (cursor);
		}
		cursor++;
	}
	return (NULL);
}

char	*texture_extraction_east(char *extraction)
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
