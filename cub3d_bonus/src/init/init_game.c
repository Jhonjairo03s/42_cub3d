/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 21:55:10 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/08/04 16:04:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->canvas = NULL;
	game->tex_n = NULL;
	game->tex_s = NULL;
	game->tex_e = NULL;
	game->tex_w = NULL;
	game->map = NULL;
	game->raw_data = NULL;
	game->player_x = 0.0;
	game->player_y = 0.0;
	game->dir_x = 0.0;
	game->dir_y = 0.0;
	game->plane_x = 0.0;
	game->plane_y = 0.0;
	game->floor_color = 0;
	game->ceil_color = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->prev_mouse_x = -1;
	game->mouse_enabled = true;
	game->show_fps = true;
}

t_i32	init_graphics(t_game *game)
{
	game->mlx = mlx_init(RESX, RESY, "cub3D_bonus", true);
	if (!game->mlx)
		return (err_msg("MLX init", "MLX42 init failed\n", -1));
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	game->canvas = mlx_new_image(game->mlx, RESX, RESY);
	if (!game->canvas)
		return (err_msg("Canvas", "canvas creation failed\n", -1));
	if (mlx_image_to_window(game->mlx, game->canvas, 0, 0) == -1)
		return (err_msg("Window", "display image failed\n", -1));
	return (0);
}

void	set_player_direction(t_game *game, char dir)
{
	game->dir_x = 0.0;
	game->dir_y = 0.0;
	game->plane_x = 0.0;
	game->plane_y = 0.0;
	if (dir == 'N')
	{
		game->dir_y = -1.0;
		game->plane_x = FOV_SCALE;
	}
	else if (dir == 'S')
	{
		game->dir_y = 1.0;
		game->plane_x = -FOV_SCALE;
	}
	else if (dir == 'E')
	{
		game->dir_x = 1.0;
		game->plane_y = FOV_SCALE;
	}
	else if (dir == 'W')
	{
		game->dir_x = -1.0;
		game->plane_y = -FOV_SCALE;
	}
}
