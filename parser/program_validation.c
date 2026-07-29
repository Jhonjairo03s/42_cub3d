/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 17:40:46 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:45:50 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Tests file accessibility and ensures the path points to a regular file,
 *        not a directory.
 *
 * @param arg The file path to test.
 * @return int 0 if the file is valid and readable, 1 if it cannot be opened
 *         (missing or bad permissions), and 2 if the path is a directory.
 *
 * @note Using O_DIRECTORY is a safe, low-level trick to check if a path
 *       is a folder without needing to include <sys/stat.h>. FDs are always
 *       safely closed before returning.
 */
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

/**
 * @brief Validates the command-line arguments and the structural naming of the
 *        provided map file.
 *
 * @param ac Argument count passed from main.
 * @param arg The file path (argv[1]) provided by the user.
 * @return int 0 if all validations pass, -1 if any check fails (printing the
 *         corresponding error message to STDERR).
 *
 * @note This function acts as the perimeter fence. It strictly enforces 
 *	     argc == 2, rejects files without the exact ".cub" extension, prevents 
 *	     malicious hidden files (e.g., "/.cub" or ".cub"), and verifies 
 *	     file integrity.
 */
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
