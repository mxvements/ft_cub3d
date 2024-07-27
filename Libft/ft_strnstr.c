/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:38:04 by zlu               #+#    #+#             */
/*   Updated: 2023/09/12 17:38:06 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strlen (needle) == 0)
		return ((char *)haystack);
	while (i < len && len > 0 && haystack[i])
	{
		if (haystack[i] == needle[j])
		{
			while (needle[j] && len >= (i + j + 1))
			{
				if (haystack[i + j] != needle[j])
					break ;
				j++;
			}
			if ((int )ft_strlen (needle) <= j)
				return ((char *)&haystack[i]);
		}
		i++;
		j = 0;
	}
	return (0);
}
