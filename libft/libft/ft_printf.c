/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:31:02 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/23 09:31:02 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_class(char input, va_list args)
{
	int	count;

	if (input == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (input == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (input == 'p')
		return (ft_putnb((unsigned long)va_arg(args, void *), 16, 3, 0));
	else if (input == 'd' || input == 'i')
		return (ft_putnb((long)va_arg(args, int), 10, 0, 0));
	else if (input == 'u')
		return (ft_putnb((long)va_arg(args, unsigned int), 10, 0, 0));
	else if (input == 'x')
		return (ft_putnb((long)va_arg(args, unsigned int), 16, 0, 0));
	else if (input == 'X')
		return (ft_putnb((long)va_arg(args, unsigned int), 16, 1, 0));
	else if (input == '%')
		return (write(1, &input, 1));
	else
		count = write(1, &input, 1);
	return (count);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, input);
	while (*input)
	{
		if (*input == '%')
		{
			input++;
			i += ft_class(*input, args);
		}
		else
			i += ft_putchar(*input);
		input++;
	}
	va_end(args);
	return (i);
}
