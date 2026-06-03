/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_of_the_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:16:48 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 12:25:00 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*read_loop(int fd, char *raw_data)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(raw_data, buffer);
		free(raw_data);
		raw_data = temp;
		if (!raw_data)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(raw_data);
		return (NULL);
	}
	return (raw_data);
}

char	*parser_map(const char *buf)
{
	int		fd;
	char	*raw_data;

	fd = open(buf, O_RDONLY);
	if (fd == -1)
		return (NULL);
	raw_data = (char *)malloc(sizeof(char) * 1);
	if (raw_data == NULL)
	{
		close(fd);
		return (NULL);
	}
	raw_data[0] = '\0';
	raw_data = read_loop(fd, raw_data);
	close(fd);
	return (raw_data);
}
