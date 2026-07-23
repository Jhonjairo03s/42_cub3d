/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 17:40:46 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/23 17:17:17 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	open_argv(const char *arg)
{
	int		fd;
	int		fd_dir;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (1);
	fd_dir = open(arg, O_RDONLY | O_DIRECTORY);
	if (fd_dir != -1)
	{
		close(fd_dir);
		close(fd);
		return (2);
	}
	close(fd);
	return (0);
}

int	program_validation(int ac, const char *arg)
{
	size_t	len;
	char	*last_slash;

	if (ac != 2)
		return (err_msg("Usage", ERROR_USAGE, -1));
	len = ft_strlen(arg);
	last_slash = ft_strrchr(arg, '/');
	if ((len < 5) || ((last_slash != NULL) && (*(last_slash + 1) == '.')))
		return (err_msg("Length", ERROR_LENGTH, -1));
	if (ft_strcmp(arg + (len - 4), ".cub") != 0)
		return (err_msg("Extension", ERROR_EXTENSION, -1));
	if (open_argv(arg) == 1)
		return (err_msg("fd open", ERROR_FD_OPEN, -1));
	if (open_argv(arg) == 2)
		return (err_msg("fd open dir", ERROR_FD_DIR_OPEN, -1));
	return (0);
}
