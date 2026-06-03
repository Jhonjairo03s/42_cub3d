/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:45:33 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/08 21:13:14 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	unsigned char	*p;
	int				i;

	p = dst;
	i = 0;
	while (n > 0)
	{
		p[i] = (unsigned char) c;
		i++;
		n--;
	}
	return (dst);
}
