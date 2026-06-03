/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:47:40 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/15 12:01:14 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*position;

	size = ft_strlen(s) + 1;
	position = malloc(size);
	if (!position)
		return (NULL);
	ft_strlcpy(position, s, size);
	return (position);
}
