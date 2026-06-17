/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:14:47 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/16 16:23:24 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_vectors(t_game *game)
{
	int	index;
	int	total_size;

	index = 0;
	total_size = game->map_width * game->map_height;
	while (index < total_size)
	{
		if (game->map[index] == 'N')
			init_vector_n(game);
		if (game->map[index] == 'S')
			init_vector_s(game);
		if (game->map[index] == 'E')
			init_vector_e(game);
		if (game->map[index] == 'W')
			init_vector_w(game);
		index++;
	}
	game->map[index] = '0';
}
