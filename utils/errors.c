/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 23:27:35 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/15 19:20:13 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	err_msg(const char *msg, char *str, int code)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (msg != NULL)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, ": ", 2);
	}
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
	return (code);
}
