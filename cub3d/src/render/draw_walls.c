/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 18:14:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	uint32_t	*dst;

	if (x < 0 || x >= RESX || y < 0 || y >= RESY)
		return ;
	if (!img || !img->addr)
		return ;
	dst = (uint32_t *)(img->addr + (y * img->line_len + (x * 4)));
	*dst = (uint32_t)color;
}

static uint32_t	sample_texture(t_img *tex, int tex_x, int tex_y)
{
	uint32_t	*pixels;
	int			pitch;

	if (!tex || !tex->addr)
		return (0x00808080);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	pitch = tex->line_len / 4;
	pixels = (uint32_t *)tex->addr;
	return (pixels[tex_y * pitch + tex_x]);
}

static void	draw_column(t_game *game, t_ray *ray, t_img *tex, int p[3])
{
	uint32_t	*buf;
	int			y;
	double		step;
	double		pos;

	buf = (uint32_t *)game->frame.addr;
	y = -1;
	while (++y < ray->draw_start)
		buf[y * RESX + p[0]] = game->ceil_color;
	step = 1.0 * tex->height / ray->line_height;
	pos = (ray->draw_start - RESY / 2.0 + ray->line_height / 2.0) * step;
	y = ray->draw_start - 1;
	while (++y <= ray->draw_end)
	{
		p[2] = (int)pos;
		pos += step;
		buf[y * RESX + p[0]] = sample_texture(tex, p[1], p[2]);
	}
	y = ray->draw_end;
	while (++y < RESY)
		buf[y * RESX + p[0]] = game->floor_color;
}

void	draw_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	double	wall_x;
	int		p[3];

	p[0] = x;
	tex = select_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (tex && tex->width > 0 && tex->height > 0)
	{
		p[1] = (int)(wall_x * (double)tex->width);
		if (ray->side == 0 && ray->ray_dir_x < 0)
			p[1] = tex->width - p[1] - 1;
		if (ray->side == 1 && ray->ray_dir_y > 0)
			p[1] = tex->width - p[1] - 1;
		draw_column(game, ray, tex, p);
	}
}

void	render(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < RESX)
	{
		ray_init(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_dist(&ray);
		if (game->z_buffer != NULL)
			game->z_buffer[x] = ray.perp_wall_dist;
		draw_wall_slice(game, &ray, x);
		x++;
	}
}
