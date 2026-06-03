/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:08:31 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/16 15:08:46 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen(int n)
{
	unsigned int	abs;
	size_t			i;

	abs = n - 2 * n * (n < 0);
	i = (n <= 0);
	while (abs > 0 && ++i)
		abs /= 10;
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	abs;
	size_t			i;
	char			*str;

	i = ft_intlen(n);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '-';
	str[i] = '\0';
	abs = n - 2 * n * (n < 0);
	while (1)
	{
		str[--i] = '0' + (abs % 10);
		abs /= 10;
		if (abs == 0)
			return (str);
	}
}
