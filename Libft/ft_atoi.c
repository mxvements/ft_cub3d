/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:06:13 by zlu               #+#    #+#             */
/*   Updated: 2024/01/15 09:42:32 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_atoi(const char *str)
{
	size_t	num;
	size_t	i;
	size_t	sig;

	sig = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'\
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sig = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((size_t)(sig * num));
}
