/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:40:20 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/07 20:40:21 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
int main(void)
{
	char	c = 'i';
	int	a = 140;

	int temp = ft_isascii(c) + 48;
	write(1, &temp, 1);
	return (0);
}*/
