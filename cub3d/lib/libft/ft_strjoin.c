/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 10:22:07 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/20 18:00:53 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_str(char *join, char *s1, char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] != '\0')
	{
		join[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index] != '\0')
	{
		join[index + ft_strlen(s1)] = s2[index];
		index++;
	}
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = NULL;
	join = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (join == NULL)
		return (NULL);
	copy_str(join, s1, s2);
	return (join);
}
