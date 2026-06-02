/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_of_the_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:16:48 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/01 11:23:02 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#if 0
char	*parser_map(const char *buf)
{
	int		fd;
	char	*buffer;
	ssize_t	n;

	fd = open(buf, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buffer = NULL;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		close(fd);
		return (NULL);
	}
	n = read(fd, buffer, BUFFER_SIZE);
	if (n == -1)
	{
		close(fd);
		return (NULL);
	}
	buffer[n] = '\0';
	close(fd);
	return (buffer);
}
#endif

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
