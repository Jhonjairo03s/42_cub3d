/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 17:56:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/07/22 17:56:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_fps_bonus(t_game *game)
{
	int		fps;
	char	*fps_str;
	char	*str;

	if (game->time_data.delta_time > 0.0001)
		fps = (int)(1.0 / game->time_data.delta_time);
	else
		fps = 60;
	fps_str = ft_itoa(fps);
	if (!fps_str)
		return ;
	str = ft_strjoin("FPS: ", fps_str);
	free(fps_str);
	if (!str)
		return ;
	mlx_string_put(game->mlx_ptr, game->win_ptr, RESX - 80, 25,
		0x00FF00, str);
	free(str);
}
