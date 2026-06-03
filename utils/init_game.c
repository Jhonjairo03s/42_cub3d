/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 21:55:10 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/05/28 22:35:02 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


t_u8 maps[64] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1
};

void	init_game(t_game *game)
{
	game->mlx = mlx_init(RESX, RESY, "Best cub3d ever", false);
	game->img = mlx_new_image(game->mlx, RESX, RESY);
	game->tex_n = NULL; // en cada uno envez de usar un ciclo para presentarlo a 0 y despues darle valor ahorramos tiempo
	game->tex_s = NULL;// todo; etc
	game->tex_e = NULL;
	game->tex_w = NULL;
	game->map = &maps[0];
	game->player_x = 7.0;
	game->player_y = 6.0;
	game->dir_x = 0.0;
	game->dir_y = -1.0;
	game->alpha = 150;
	game->plane_x = 0.66;
	game->plane_y = 0.0;
	game->floor_color = 0;
	game->ceil_color = 0;
	game->map_width = 8;
	game->map_height = 8;
	game->show_fps = false;
}
