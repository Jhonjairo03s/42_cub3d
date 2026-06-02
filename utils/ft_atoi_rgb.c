/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:01:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/02 11:43:18 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_atoi_rgb(char **str)
{
	int	result;
	int	sign;

	while (**str == ' ')
		(*str)++;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	if (**str == '+')
		(*str)++;
	while (**str >= '0' && **str <= '9')
	{
		result = (result * 10) + (**str - '0');
		(*str)++;
	}
	return (result * sign);
}
