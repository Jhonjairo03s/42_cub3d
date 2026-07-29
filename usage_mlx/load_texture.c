/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:27:14 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:46:16 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
t_u32	*load_texture(t_game *game, char *path, void **save_img_ptr)
{
	t_texture	tex;

	*save_img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &tex.width,
			&tex.height);
	if (*save_img_ptr == NULL)
		return (NULL);
	tex.pixels = (uint32_t *)mlx_get_data_addr(*save_img_ptr, &tex.bpp,
			&tex.size_line, &tex.endian);
	return (tex.pixels);
}
*/

/**
 * @brief Simple string checker to verify if a file uses the .png extension.
 *
 * @param path The file path to check.
 * @return int 1 if the file is a PNG, 0 otherwise.
 */
static int	is_png(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len >= 4 && ft_strcmp(path + len - 4, ".png") == 0)
		return (1);
	return (0);
}

/**
 * @brief Loads an XPM42 file and extracts its underlying texture data into a
 *        standalone texture structure.
 *
 * @param path The file path to the .xpm42 file.
 * @return mlx_texture_t* A dynamically allocated texture structure containing
 *         the image data, or NULL on failure.
 *
 * @note MLX42 handles XPMs wrapped in a specific `xpm_t` struct. This function
 *       bypasses the wrapper by allocating a pure `mlx_texture_t`, copying the
 *       internal pointers, and freeing the outer wrapper.
 */
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

/**
 * @brief Universal texture loader that abstracts the file format from the 
 *		  engine.
 *
 * @param path The file path of the texture to load.
 * @return mlx_texture_t* The standardized loaded texture, or NULL if it fails.
 *
 * @note This is a Factory pattern. It automatically routes the file to the
 *       correct MLX42 parser (.png or .xpm42) and always returns a unified
 *       `mlx_texture_t` format. The rendering engine will never need to know
 *       which image format was originally provided in the .cub file.
 */
mlx_texture_t	*load_texture_agnostic(char *path)
{
	mlx_texture_t	*tex;

	if (is_png(path) == 1)
		tex = mlx_load_png(path);
	else
		tex = extract_xpm_to_tex(path);
	if (tex == NULL)
		return (NULL);
	return (tex);
}
