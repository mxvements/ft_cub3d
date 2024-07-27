/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:01:53 by zlu               #+#    #+#             */
/*   Updated: 2024/06/29 12:58:03 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	ptr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (0);
	while (i < (s1_len + s2_len))
	{
		if (i < s1_len)
			ptr[i] = s1[i];
		else
			ptr[i] = s2[i - s1_len];
		i++;
	}
	ptr[i] = 0;
	free((char *)s1);
	return (ptr);
}
