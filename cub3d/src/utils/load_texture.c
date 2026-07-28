/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:27:14 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 15:40:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_png(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len >= 4 && ft_strcmp(path + len - 4, ".png") == 0)
		return (1);
	return (0);
}

static mlx_texture_t	*extract_xpm_to_tex(char *path)
{
	xpm_t			*xpm;
	mlx_texture_t	*tex;

	xpm = mlx_load_xpm42(path);
	if (xpm == NULL)
		return (NULL);
	tex = (mlx_texture_t *)malloc(sizeof(mlx_texture_t));
	if (tex == NULL)
	{
		mlx_delete_xpm42(xpm);
		return (NULL);
	}
	tex->width = xpm->texture.width;
	tex->height = xpm->texture.height;
	tex->bytes_per_pixel = xpm->texture.bytes_per_pixel;
	tex->pixels = xpm->texture.pixels;
	free(xpm);
	return (tex);
}

mlx_texture_t	*load_texture_agnostic(char *path)
{
	mlx_texture_t	*tex;
	char			*png_path;
	size_t			len;

	if (is_png(path) == 1)
		tex = mlx_load_png(path);
	else
		tex = extract_xpm_to_tex(path);
	if (tex == NULL)
	{
		len = ft_strlen(path);
		if (len >= 4 && ft_strcmp(path + len - 4, ".xpm") == 0)
		{
			png_path = ft_strjoin(path, "");
			if (png_path)
			{
				png_path[len - 3] = 'p';
				png_path[len - 2] = 'n';
				png_path[len - 1] = 'g';
				tex = mlx_load_png(png_path);
				free(png_path);
			}
		}
	}
	return (tex);
}
