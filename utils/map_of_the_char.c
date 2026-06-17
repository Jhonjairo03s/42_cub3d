/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_of_the_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:16:48 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/10 23:17:01 by jhvalenc         ###   ########.fr       */
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
