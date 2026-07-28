/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:27:14 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:47:00 by jhvalenc         ###   ########.fr       */
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

static t_u8	*copy_pixels(t_u8 *src, t_u32 w, t_u32 h, t_u32 bpp)
{
	t_u8	*dst;
	size_t	size;
	size_t	i;

	size = (size_t)(w * h * bpp);
	dst = (t_u8 *)malloc(size);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static mlx_texture_t	*extract_xpm_to_tex(char *path)
{
	xpm_t			*xpm;
	mlx_texture_t	*tex;

	xpm = mlx_load_xpm42(path);
	if (xpm == NULL)
		return (NULL);
	tex = (mlx_texture_t *)malloc(sizeof(mlx_texture_t));
	if (!tex)
	{
		mlx_delete_xpm42(xpm);
		return (NULL);
	}
	tex->width = xpm->texture.width;
	tex->height = xpm->texture.height;
	tex->bytes_per_pixel = xpm->texture.bytes_per_pixel;
	tex->pixels = copy_pixels(xpm->texture.pixels,
			tex->width, tex->height, tex->bytes_per_pixel);
	mlx_delete_xpm42(xpm);
	if (!tex->pixels)
	{
		free(tex);
		return (NULL);
	}
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
