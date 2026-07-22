/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	init_graphics(t_game *game)
{
	if (!game->mlx_ptr)
		return (err_msg("MLX init", ERROR_FD_OPEN, 1));
	game->win_ptr = mlx_new_window(game->mlx_ptr, RESX, RESY, "cub3D");
	if (!game->win_ptr)
		return (err_msg("Window creation", ERROR_FD_OPEN, 1));
	game->frame.img_ptr = mlx_new_image(game->mlx_ptr, RESX, RESY);
	if (!game->frame.img_ptr)
		return (err_msg("Image creation", ERROR_FD_OPEN, 1));
	game->frame.addr = mlx_get_data_addr(game->frame.img_ptr, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	game->frame.width = RESX;
	game->frame.height = RESY;
	return (0);
}
