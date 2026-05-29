/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/05/29 00:50:51 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	program_validation(const char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len < 5)
		return (err_msg("Length", ERROR_LENGTH, 1));
	if (ft_strcmp(arg + (len - 4), ".cub") != 0)
		return (err_msg("Extension", ERROR_EXTENSION, 1));
	return (0);
}

int	main(int argc, char **argv)
{
	// t_game	game;

	if (argc != 2)
		return (err_msg("Usage", ERROR_USAGE, 1));
	if (program_validation(argv[1]) == 1)
		return (1);
	// init_game(&game);
	write(STDOUT_FILENO, "OK\n", 3);
	return (0);
}
