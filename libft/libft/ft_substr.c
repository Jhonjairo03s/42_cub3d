/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:01:39 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/18 14:45:20 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*end;
	unsigned int	fl;

	if (!s)
		return (NULL);
	fl = ft_strlen(s);
	if (start > fl)
		return (ft_calloc(sizeof(char), 1));
	if (start + len > fl)
		len = fl - start;
	end = malloc(sizeof(char) * (len + 1));
	if (!end)
		return (NULL);
	ft_strlcpy(end, &s[start], len + 1);
	return (end);
}

/*int main(void)
{
	char *str = "Hello, World!";
	char *substr = ft_substr(str, 0, 10);
	printf("Substring: %s\n", substr); // Should print "World"
	free(substr); // Don't forget to free the allocated memory
	return 0;
}
*/