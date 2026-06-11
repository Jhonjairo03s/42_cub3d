/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 23:27:35 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/05/28 23:55:10 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	err_msg(const char *msg, char *str, int code)
{
	ssize_t	ret;

	ret = write(STDERR_FILENO, "Error - ", 8);
	if (msg != NULL)
	{
		ret = write(STDERR_FILENO, msg, ft_strlen(msg));
		ret = write(STDERR_FILENO, ": ", 2);
	}
	if (str != NULL)
		ret = write(STDERR_FILENO, str, ft_strlen(str));
	(void)ret;
	return (code);
}
