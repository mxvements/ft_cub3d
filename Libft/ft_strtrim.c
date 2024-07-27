/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:07:25 by zlu               #+#    #+#             */
/*   Updated: 2024/06/26 18:19:33 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		f;
	char	*s1_c;
	char	*set_c;

	set_c = (char *)set;
	s1_c = (char *)s1;
	i = 0;
	f = ft_strlen(s1_c);
	if (!s1_c || !set_c)
		return (NULL);
	while (s1_c[i] && ft_strchr(set, s1_c[i]))
		i++;
	while (f > i && ft_strrchr(set, s1_c[f - 1]))
		f--;
	s1_c = ft_substr(s1_c, i, f - i);
	if (!s1_c)
		return (free(s1_c), NULL);
	return (s1_c);
}
