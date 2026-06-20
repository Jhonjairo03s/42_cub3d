/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 23:27:35 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/20 19:48:28 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	err_msg(const char *msg, char *str, int code)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (msg != NULL)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, ": ", 2);
	}
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
	return (code);
}

int	free_and_return(t_u8 *map, t_point *stack, int code)
{
	free(map);
	free(stack);
	return (code);
}

void	clean_exit(t_game *game)
{
	if (game->img_n != NULL)
		mlx_destroy_image(game->mlx_ptr, game->img_n);
	if (game->img_s != NULL)
		mlx_destroy_image(game->mlx_ptr, game->img_s);
	if (game->img_e != NULL)
		mlx_destroy_image(game->mlx_ptr, game->img_e);
	if (game->img_w != NULL)
		mlx_destroy_image(game->mlx_ptr, game->img_w);
	if (game->mlx_ptr != NULL)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (game->raw_data != NULL)
		free(game->raw_data);
	if (game->map != NULL)
		free(game->map);
	free(game);
}
