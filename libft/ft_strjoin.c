/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 10:22:07 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/01 10:41:03 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	len_s1;
	size_t	len_s2;
	size_t	index;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = NULL;
	join = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (join == NULL)
		return (NULL);
	index = 0;
	while (index < len_s1)
	{
		join[index] = s1[index];
		index++;
	}
	index = 0;
	while (index < len_s2)
	{
		join[index + len_s1] = s2[index];
		index++;
	}
	join[len_s1 + len_s2] = '\0';
	return (join);
}
