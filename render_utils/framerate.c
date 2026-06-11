/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:25:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 12:25:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*framecalc(t_game *game)
{
	static int	i;
	static char	str[16];
	char		*tmp;
	double		sum;
	int			j;

	if (!game || !game->mlx || !game->framedata)
		return ("0");
	game->framedata->frame_times[i] = game->mlx->delta_time;
	i = (i + 1) % 5;
	if (game->framedata->count < 5)
		game->framedata->count++;
	sum = 0;
	j = 0;
	while (j < game->framedata->count)
	{
		sum += game->framedata->frame_times[j];
		j++;
	}
	if (sum == 0)
		return ("0");
	tmp = ft_itoa((int)(1.0 / (sum / game->framedata->count)));
	ft_strlcpy(str, tmp, 16);
	free(tmp);
	return (str);
}
