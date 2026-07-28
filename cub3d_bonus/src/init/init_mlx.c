/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 16:35:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_i32	init_graphics(t_game *game)
{
	game->mlx = mlx_init(RESX, RESY, "cub3D_bonus", true);
	if (!game->mlx)
		return (err_msg("MLX init", "MLX42 init failed\n", -1));
	game->canvas = mlx_new_image(game->mlx, RESX, RESY);
	if (!game->canvas)
		return (err_msg("Canvas", "canvas creation failed\n", -1));
	if (mlx_image_to_window(game->mlx, game->canvas, 0, 0) == -1)
		return (err_msg("Window", "display image failed\n", -1));
	return (0);
}
