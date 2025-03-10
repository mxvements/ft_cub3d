/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:53 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:54 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_int_ptr(int **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_map(void *data)
{
	t_map	*map;

	map = data;
	if (map->map)
		strarr_freenull(&map->map);
	if (map->player)
	{
		free(map->player);
		map->player = NULL;
	}
}

void	free_struct(void **s, void (*free_s)(void *))
{
	if (*s)
	{
		free_s(*s);
		free(*s);
		*s = NULL;
	}
}

/**
 * @brief Clean the static variable inside the call of get_next_line
 * This is necessary in oorder not to get 'still reachable' leaks when we have
 * an error mid-file reading.
 * Call this function always before closing the fd
 * @param fd
 */
void	clean_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
