/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:59:28 by zlu               #+#    #+#             */
/*   Updated: 2023/09/30 18:59:36 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_memsplit(char const *s, char c)
{
	int		i;
	int		cont;
	char	*s_c;
	char	**res;

	s_c = (char *)s;
	i = 0;
	cont = 0;
	if (!s_c)
		return (0);
	while (s_c[i])
	{
		while (s_c[i] == c)
			i++;
		if (s_c[i])
			cont++;
		while (s_c[i] != c && s_c[i])
			i++;
	}
	res = (char **)malloc((cont + 1) * sizeof(char *));
	if (res == NULL || s == 0)
		cont = 0;
	return (res);
}

static int	ft_splitlen(char const *s, char c, int i)
{
	char	*s_c;
	int		len;

	s_c = (char *)s;
	if (ft_strchr(s_c + i, c))
		len = ft_strchr(s_c + i, c) - (s_c + i);
	else
		len = ft_strlen(s_c + i);
	return (len);
}

static int	ft_freesplit(char **res, int j )
{
	int	i;

	i = 1;
	j = j - 1;
	if (!res[j])
	{
		while (j >= 0)
		{
			free(res[j]);
			j--;
		}
		free(res);
		i = 0;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		len;

	j = 0;
	res = ft_memsplit((char *)s, c);
	if (res == 0)
		return (NULL);
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			len = ft_splitlen(s, c, i);
			res[j++] = ft_substr(s + i, 0, len);
			if (ft_freesplit(res, j) == 0)
				return (NULL);
			i += len;
		}
	}
	res[j] = NULL;
	return (res);
}
