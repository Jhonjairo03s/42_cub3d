/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:00:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:47:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (game->tex_e);
		return (game->tex_w);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (game->tex_s);
		return (game->tex_n);
	}
}

t_u32	sample_texture(mlx_texture_t *tex, t_i32 tex_x, t_i32 tex_y)
{
	t_i32	index;
	t_u32	r;
	t_u32	g;
	t_u32	b;
	t_u32	a;

	if (!tex || !tex->pixels)
		return (0x808080FF);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (t_i32)tex->width)
		tex_x = tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (t_i32)tex->height)
		tex_y = tex->height - 1;
	index = (tex_y * tex->width + tex_x) * 4;
	r = tex->pixels[index];
	g = tex->pixels[index + 1];
	b = tex->pixels[index + 2];
	a = tex->pixels[index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
