/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:27:14 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 17:51:00 by ppaula-s         ###   ########.fr       */
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

static void	*open_xpm(void *mlx_ptr, char *path, int *w, int *h)
{
	void	*ptr;
	char	*xpm_path;

	xpm_path = get_xpm_path(path);
	ptr = NULL;
	if (xpm_path)
	{
		ptr = mlx_xpm_file_to_image(mlx_ptr, xpm_path, w, h);
		free(xpm_path);
	}
	if (!ptr)
		ptr = mlx_xpm_file_to_image(mlx_ptr, path, w, h);
	return (ptr);
}

t_img	*load_texture(void *mlx_ptr, char *path)
{
	t_img	*img;

	if (!mlx_ptr || !path)
		return (NULL);
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	ft_memset(img, 0, sizeof(t_img));
	img->img_ptr = open_xpm(mlx_ptr, path, &img->width, &img->height);
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
		return (game->tex_e);
	}
	if (ray->ray_dir_y < 0)
		return (game->tex_n);
	return (game->tex_s);
}
