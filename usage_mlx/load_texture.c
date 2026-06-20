/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:27:14 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/18 12:38:35 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
 * Crea un objeto imagen a partir de un archivo .xpm usando la mlx.
 *
 * Extrae la dirección de memoria cruda de los píxeles para que el motor
 * de renderizado (Raycaster) pueda leer los colores directamente 
 * desde la RAM (O(1)), sin necesidad de usar las funciones lentas de mlx.
 *
 * Además, guarda el puntero de la imagen (img_ptr) por referencia para
 * poder liberarlo con mlx_destroy_image() al cerrar el programa.
*/

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
