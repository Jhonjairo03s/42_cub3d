/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:10:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 12:10:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_fps(t_game *game)
{
	char	*fps_str;
	int		fps;

	if (game->fps_img)
	{
		mlx_delete_image(game->mlx, game->fps_img);
		game->fps_img = NULL;
	}
	if (!game->show_fps)
		return ;
	if (game->mlx->delta_time > 0)
		fps = (int)(1.0 / game->mlx->delta_time);
	else
		fps = 0;
	fps_str = ft_itoa(fps);
	if (fps_str)
	{
		game->fps_img = mlx_put_string(game->mlx, fps_str, 0, 0);
		free(fps_str);
	}
}
