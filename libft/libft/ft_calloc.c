/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:37:39 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/09 02:21:15 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = malloc(size * nmemb);
	if (!ret)
		return (0);
	ft_bzero(ret, size * nmemb);
	return (ret);
}
