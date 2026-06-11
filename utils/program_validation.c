/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:30:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 12:30:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	program_validation(const char *arg)
{
	size_t	len;
	int		fd;
	int		fd_dir;

	len = ft_strlen(arg);
	if (len < 5)
		return (err_msg("Length", ERROR_LENGTH, 1));
	if (ft_strcmp(arg + (len - 4), ".cub") != 0)
		return (err_msg("Extension", ERROR_EXTENSION, 1));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg("fd open", ERROR_FD_OPEN, 1));
	fd_dir = open(arg, O_RDONLY | O_DIRECTORY);
	if (fd_dir != -1)
	{
		close(fd_dir);
		close(fd);
		return (err_msg("fd open dir", ERROR_FD_DIR_OPEN, 1));
	}
	close(fd);
	return (0);
}
