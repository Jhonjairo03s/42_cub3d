/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:11:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/01 12:05:41 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	program_validation(const char *arg)
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
		return (err_msg("fd opem", ERROR_FD_OPEN, 1));
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

int	main(int argc, char **argv)
{
	const char	*buf;
	char	*raw_data;
	char	*cursor;

	if (argc != 2)
		return (err_msg("Usage", ERROR_USAGE, 1));
	if (program_validation(argv[1]) == 1)
		return (1);
	raw_data = parser_map(argv[1]);
	if (raw_data == NULL)
	{
		buf = "Fallo parser_map\n";
		write(STDERR_FILENO, buf, ft_strlen(buf));
		return (1);
	}
	cursor = explore_map(raw_data, "SO");
	if (cursor == NULL)
	{
		buf = "Fallo explore_map\n";
		write(STDERR_FILENO, buf, ft_strlen(buf));
		free(raw_data);
		return (1);
	}
	cursor = extract_texture_path(cursor);
	if (cursor == NULL)
	{
		buf = "Fallo texture_extraction\n";
		write(STDERR_FILENO, buf, ft_strlen(buf));
		free(raw_data);
		return (1);
	}
	write(STDOUT_FILENO, "Inicio\n", 7);
	write(STDOUT_FILENO, cursor, ft_strlen(cursor));
	write(STDOUT_FILENO, "\nFin\n", 5);
	free(raw_data);
	return (0);
}
