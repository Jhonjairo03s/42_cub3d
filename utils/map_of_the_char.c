/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_of_the_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:16:48 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:42:42 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
char	*parser_map(const char *buf)
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	char	*raw_data;
	char	*temp;
	ssize_t	bytes_read;

	fd = open(buf, O_RDONLY);
	if (fd == -1)
		return (NULL);
	raw_data = NULL;
	raw_data = (char *)malloc(sizeof(char) * 1);
	if (raw_data == NULL)
	{
		close(fd);
		return (NULL);
	}
	raw_data[0] = '\0';
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) >= 0)
	{
		if (bytes_read == -1)
		{
			close(fd);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(raw_data, buffer);
		free(raw_data);
		raw_data = temp;
	}
	close(fd);
	return (raw_data);
}
*/

/**
 * @brief Reads data from a file descriptor in chunks and concatenates it
 *        into a single dynamically allocated string.
 *
 * @param fd The open file descriptor to read from.
 * @param raw_d The initial heap-allocated string (usually just "\0")
 *	      to append to.
 * @return char* A pointer to the newly allocated string containing all the
 *         accumulated data, or NULL if reading or memory allocation fails.
 *
 * @note This function safely manages memory by freeing the old `raw_d` string
 *       during each `ft_strjoin` cycle, preventing leaks while the string grows.
 */
char	*concatenate(int fd, char *raw_d)
{
	ssize_t	bytes_read;
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(raw_d, buffer);
		free(raw_d);
		if (temp == NULL)
			return (NULL);
		raw_d = temp;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(raw_d);
		return (NULL);
	}
	return (raw_d);
}

/**
 * @brief Opens the .cub file and extracts its entire content into a single
 *        continuous string in memory.
 *
 * @param buf The file path string (e.g., argv[1]).
 * @return char* A pointer to the full raw file content (heap-allocated string),
 *         or NULL if file opening, reading, or memory allocation fails.
 *
 * @note It kickstarts the extraction by allocating a 1-byte empty string ("\0")
 *       so ft_strjoin has a valid starting point. The caller (main structure)
 *       is responsible for freeing this memory later (via clean_exit).
 */
char	*parser_map(const char *buf)
{
	int		fd;
	char	*raw_data;

	fd = open(buf, O_RDONLY);
	if (fd == -1)
		return (NULL);
	raw_data = NULL;
	raw_data = (char *)malloc(sizeof(char) * 1);
	if (raw_data == NULL)
	{
		close(fd);
		return (NULL);
	}
	raw_data[0] = '\0';
	raw_data = concatenate(fd, raw_data);
	if (raw_data == NULL)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (raw_data);
}
