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
#include <sys/time.h>

static void	set_map_data(t_game *game)
{
	int		i;
	char	*str;

	str = "1111111110000001100001011001000110000001101000011000000111111111";
	game->map = malloc(64);
	if (!game->map)
		return ;
	i = -1;
	while (++i < 64)
		game->map[i] = str[i];
	game->map_width = 8;
	game->map_height = 8;
}

static void	init_player_and_time(t_game *game)
{
	game->player_x = 1.5;
	game->player_y = 1.5;
	game->dir_x = 0.0;
	game->dir_y = -1.0;
	game->alpha = 150;
	game->plane_x = 0.66;
	game->plane_y = 0.0;
	game->time_data.last_time = get_time_in_ms();
	game->time_data.anim_timer = 0;
	game->time_data.sprite_frame = 0;
	game->enemy.x = 6.5;
	game->enemy.y = 6.5;
	game->enemy.speed = 1.0;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(RESX, RESY, "Best cub3d ever", false);
	game->img = mlx_new_image(game->mlx, RESX, RESY);
	game->tex_n = NULL;
	game->tex_s = NULL;
	game->tex_e = NULL;
	game->tex_w = NULL;
	set_map_data(game);
	init_player_and_time(game);
	game->floor_color = 0;
	game->ceil_color = 0;
	game->show_fps = false;
	game->z_buffer = malloc(sizeof(float) * RESX);
}

int64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

void	update_enemy(t_game *game, long long elapsed)
{
	double	factor;
	double	dx;
	double	dy;
	double	dist;

	factor = elapsed / 1000.0;
	dx = game->player_x - game->enemy.x;
	dy = game->player_y - game->enemy.y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 0.1)
	{
		game->enemy.x += (dx / dist) * game->enemy.speed * factor;
		game->enemy.y += (dy / dist) * game->enemy.speed * factor;
	}
}
