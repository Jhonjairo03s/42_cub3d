/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:00:04 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/23 08:00:04 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr(char *str)
{
	if (!str)
		return (ft_putstr("(null)"));
	return (write(1, str, ft_strlen(str)));
}

int	ft_ptr(long n, int base, int boo, int len)
{
	if (n >= base)
		len = ft_putnb(n / base, base, boo, len);
	if (boo == 1)
		len += ft_putchar(UPBASE[n % base]);
	else
		len += ft_putchar(LOWBASE[n % base]);
	return (len);
}

int	ft_putnb(long n, int base, int boo, int len)
{
	unsigned long	un;

	if (boo == 3 && len == 0 && n == 0)
		return (ft_putstr("(nil)"));
	if (boo == 3 && len == 0)
		len += ft_putstr("0x");
	if (boo == 3)
	{
		un = (unsigned long)n;
		if (un >= (unsigned long)base)
			len = ft_putnb(un / base, base, boo, len);
		len += ft_putchar(LOWBASE[un % base]);
		return (len);
	}
	if (n < 0)
	{
		len += write(1, "-", 1);
		n = -n;
	}
	len = ft_ptr(n, base, boo, len);
	return (len);
}
