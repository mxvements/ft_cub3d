/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:07:10 by zlu               #+#    #+#             */
/*   Updated: 2023/09/14 12:07:12 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	ptr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < (s1_len + s2_len))
	{
		if (i < s1_len)
			ptr[i] = s1[i];
		else
			ptr[i] = s2[i - s1_len];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
