/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 20:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/08/04 16:16:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_fps_image(t_game *game, mlx_image_t **fps_img,
				t_i32 *last_fps)
{
	if (*fps_img)
	{
		mlx_delete_image(game->mlx, *fps_img);
		*fps_img = NULL;
	}
	*last_fps = -1;
}

void	draw_fps(t_game *game)
{
	static mlx_image_t	*fps_img = NULL;
	static t_i32		last_fps = -1;
	char				*str;
	t_i32				fps;

	if (!game || !game->mlx || !game->show_fps)
	{
		clear_fps_image(game, &fps_img, &last_fps);
		return ;
	}
	if (game->mlx->delta_time > 0)
		fps = (t_i32)(1.0 / game->mlx->delta_time);
	else
		fps = 60;
	if (fps == last_fps && fps_img != NULL)
		return ;
	last_fps = fps;
	if (fps_img)
		mlx_delete_image(game->mlx, fps_img);
	str = ft_itoa(fps);
	if (!str)
		return ;
	fps_img = mlx_put_string(game->mlx, str, RESX - 50, 15);
	free(str);
}
