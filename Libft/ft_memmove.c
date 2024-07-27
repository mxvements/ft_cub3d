/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:08:28 by zlu               #+#    #+#             */
/*   Updated: 2023/09/11 19:08:32 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_c;
	char	*src_c;

	dst_c = (char *)dst;
	src_c = (char *)src;
	if (!dst_c && !src_c)
		return (0);
	if (dst_c > src_c)
	{
		while (len--)
			dst_c[len] = src_c[len];
	}
	else
		ft_memcpy(dst_c, src_c, len);
	return (dst_c);
}
