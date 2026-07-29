/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:01:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:41:17 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Custom string-to-integer converter specifically designed for RGB
 *        channel extraction and strict syntax validation.
 *
 * @param str Double pointer to the current reading position in the color 
 *	      string.
 * @return int The parsed integer value, or -1 if the syntax is invalid.
 *
 * @note Unlike a standard atoi, this custom function strictly rejects explicit
 *       signs ('+' or '-'), ensures at least one digit is present, and verifies
 *       that the extracted number is immediately followed by a valid RGB 
 *       separator (a comma, newline, or null terminator),
 *       skipping any trailing spaces.
 *       It modifies the cursor pointer in place to set up the next extraction.
 */
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
