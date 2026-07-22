/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 23:27:35 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	free_and_return(t_u8 *map, t_point *stack, int code)
{
	free(map);
	free(stack);
	return (code);
}

static void	free_texture_img(void *mlx_ptr, t_img *img)
{
	if (!img)
		return ;
	if (img->img_ptr && mlx_ptr)
		mlx_destroy_image(mlx_ptr, img->img_ptr);
	free(img);
}

void	clean_exit(t_game *game)
{
	if (!game)
		return ;
	free_texture_img(game->mlx_ptr, game->tex_n);
	free_texture_img(game->mlx_ptr, game->tex_s);
	free_texture_img(game->mlx_ptr, game->tex_e);
	free_texture_img(game->mlx_ptr, game->tex_w);
	if (game->frame.img_ptr && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, game->frame.img_ptr);
	if (game->win_ptr && game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (game->raw_data != NULL)
		free(game->raw_data);
	if (game->map != NULL)
		free(game->map);
	if (game->z_buffer != NULL)
		free(game->z_buffer);
	free(game);
}
