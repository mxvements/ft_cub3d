/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:58:13 by zlu               #+#    #+#             */
/*   Updated: 2023/09/12 12:58:15 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	int		z;

	i = 0;
	j = 0;
	z = 0;
	while (dst[j] != '\0' && j < dstsize)
		j++;
	while (src[i] != '\0')
		i++;
	if (j == dstsize)
		return (i + dstsize);
	while (src[z] != '\0' && j + z < dstsize - 1)
	{
		dst[j + z] = src[z];
		z++;
	}
	dst[j + z] = '\0';
	return (j + i);
}
