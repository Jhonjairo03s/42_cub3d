/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:00:28 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/27 17:00:28 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*newline_pos;

	newline_pos = ft_strchr(buffer, '\n');
	if (!newline_pos)
		return ;
	j = newline_pos - buffer + 1;
	i = 0;
	while (buffer[j])
		buffer[i++] = buffer[j++];
	buffer[i] = '\0';
}

static char	*gnl_init_line(char *buffer)
{
	char	*line;

	if (buffer[0])
		line = ft_strdup(buffer);
	else
	{
		line = malloc(1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	return (line);
}

static char	*gnl_ra(int fd, char *buffer, char *line, int *bytes_read)
{
	char	*tmp;

	while (!ft_strchr(buffer, '\n') && *bytes_read != 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			buffer[0] = '\0';
			free(line);
			return (NULL);
		}
		buffer[*bytes_read] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
		if (!line)
			return (NULL);
	}
	return (line);
}

static char	*gnl_trim_line(char *line, int *nl_pos)
{
	char	*tmp;
	char	*newline_pos;

	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
	{
		*nl_pos = newline_pos - line;
		tmp = malloc(*nl_pos + 2);
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		ft_strlcpy(tmp, line, *nl_pos + 2);
		free(line);
		line = tmp;
	}
	else
		*nl_pos = -1;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;
	int			nl_pos;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	line = gnl_init_line(buffer);
	if (!line)
		return (NULL);
	line = gnl_ra(fd, buffer, line, &bytes_read);
	if (!line)
		return (NULL);
	line = gnl_trim_line(line, &nl_pos);
	if (!line || (line[0] == '\0' && bytes_read == 0))
	{
		free(line);
		return (NULL);
	}
	update_buffer(buffer);
	return (line);
}
/* 
int	main(int ac, char **av)
{
	int		fd;
	char	*h;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	h = get_next_line(fd);
	while (h != NULL)
	{
		printf("%s", h);
		free(h);
		h = get_next_line(fd);
	}
	close(fd);
	return (0);
}
 */