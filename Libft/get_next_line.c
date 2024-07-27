/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:01:44 by zlu               #+#    #+#             */
/*   Updated: 2023/12/21 16:10:26 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	allfree(char **mem, char **buffer)
{
	if (*mem)
		free(*mem);
	*mem = NULL;
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
}

char	*newbuffer(char *buffer)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	i += (buffer[i] == '\n');
	aux = (char *)ft_calloc((1 + ft_strlen(buffer) - i), sizeof(char));
	if (!aux)
		return (NULL);
	j = 0;
	while (buffer[i + j])
	{
		aux[j] = buffer[i + j];
		j++;
	}
	free(buffer);
	return (aux);
}

char	*read_line(char *buffer)
{
	int		i;
	char	*new;

	i = 0;
	if (!buffer || ft_strlen(buffer) == 0)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	new = (char *)malloc((i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new[i] = buffer [i];
		i++;
	}
	if (buffer[i] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*mem;
	int			count;

	count = 1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	mem = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!mem)
		return (NULL);
	while (!(ft_strchr(buffer, '\n')) && count != 0)
	{
		count = read(fd, mem, BUFFER_SIZE);
		if (count == -1)
		{
			allfree(&mem, &buffer);
			return (NULL);
		}
		mem[count] = '\0';
		buffer = ft_strjoin_gnl(buffer, mem);
	}
	free(mem);
	mem = read_line(buffer);
	buffer = newbuffer(buffer);
	return (mem);
}
