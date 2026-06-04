/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:01:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/03 11:10:48 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_atoi_rgb(char **str)
{
	int	result;
	int	digits;

	result = 0;
	digits = 0;
	while (**str == ' ')
		(*str)++;
	if (**str == '-' || **str == '+')
		return (-1);
	while (**str >= '0' && **str <= '9')
	{
		result = (result * 10) + (**str - '0');
		(*str)++;
		digits++;
	}
	if (digits == 0)
		return (-1);
	while (**str == ' ')
		(*str)++;
	if (**str != ',' && **str != '\n' && **str != '\0')
		return (-1);
	return (result);
}
