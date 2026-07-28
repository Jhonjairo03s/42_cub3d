/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 23:27:35 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 16:03:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_i32	err_msg(const char *msg, char *str, t_i32 code)
{
	ssize_t	ret;

	ret = write(STDERR_FILENO, "Error\n", 6);
	if (msg != NULL)
	{
		ret = write(STDERR_FILENO, msg, ft_strlen(msg));
		ret = write(STDERR_FILENO, ": ", 2);
	}
	if (str != NULL)
		ret = write(STDERR_FILENO, str, ft_strlen(str));
	(void)ret;
	return (code);
}

t_i32	free_and_return(t_u8 *map, t_point *stack, t_i32 code)
{
	free(map);
	free(stack);
	return (code);
}

void	clean_exit(t_game *game)
{
	if (game == NULL)
		return ;
	if (game->tex_n != NULL)
		mlx_delete_texture(game->tex_n);
	if (game->tex_s != NULL)
		mlx_delete_texture(game->tex_s);
	if (game->tex_e != NULL)
		mlx_delete_texture(game->tex_e);
	if (game->tex_w != NULL)
		mlx_delete_texture(game->tex_w);
	if (game->mlx != NULL)
		mlx_terminate(game->mlx);
	if (game->raw_data != NULL)
		free(game->raw_data);
	if (game->map != NULL)
		free(game->map);
	free(game);
}
