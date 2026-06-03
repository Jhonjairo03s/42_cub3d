/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:51:41 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/14 14:52:11 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	i;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	lendst = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && lendst + 1 < dstsize)
	{
		dst[lendst] = src[i];
		lendst++;
		i++;
	}
	dst[lendst] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
