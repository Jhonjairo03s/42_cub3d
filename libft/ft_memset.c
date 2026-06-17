/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:30:02 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/15 20:35:12 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*buf;
	size_t			index;

	buf = (unsigned char *)s;
	index = 0;
	while (index < len)
	{
		buf[index] = (unsigned char)c;
		index++;
	}
	return (buf);
}
