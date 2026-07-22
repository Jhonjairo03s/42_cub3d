/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:27:14 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*get_xpm_path(char *path)
{
	char	*xpm_path;
	size_t	len;

	if (!path)
		return (NULL);
	xpm_path = ft_strjoin(path, "");
	if (!xpm_path)
		return (NULL);
	len = ft_strlen(xpm_path);
	if (len >= 4 && ft_strcmp(xpm_path + len - 4, ".png") == 0)
	{
		xpm_path[len - 3] = 'x';
		xpm_path[len - 2] = 'p';
		xpm_path[len - 1] = 'm';
	}
	return (xpm_path);
}

t_img	*load_texture(void *mlx_ptr, char *path)
{
	t_img	*img;
	char	*xpm_path;

	if (!mlx_ptr || !path)
		return (NULL);
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	ft_memset(img, 0, sizeof(t_img));
	xpm_path = get_xpm_path(path);
	if (xpm_path)
	{
		img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, xpm_path,
				&img->width, &img->height);
		free(xpm_path);
	}
	if (!img->img_ptr)
	{
		img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path,
				&img->width, &img->height);
	}
	if (!img->img_ptr)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	return (img);
}

t_img	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (game->tex_w);
		else
			return (game->tex_e);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (game->tex_n);
		else
			return (game->tex_s);
	}
}
