/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:29:10 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/05/28 22:37:31 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}
