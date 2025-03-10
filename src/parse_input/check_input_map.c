/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:27 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:28 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Function that takes the line to append to the map and checks if all
 * the chars contained are permitted by the program:
 *
 * + chars of map:		' ', '0', '1','\n'
 *
 * + chars  of player:	'N','E','S','W'
 *
 * @param line
 * @return int length evaluated
 */
int	is_permitted_char(char *line)
{
	const char	permitted[9] = {' ', '0', '1', '\n', '\t', 'N', 'E', 'S', 'W'};
	int			i;
	int			j;
	int			flag;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		j = -1;
		while (permitted[++j])
		{
			if (line[i] == permitted[j])
			{
				flag = 0;
				break ;
			}
			if (line[i] != permitted[j])
				flag = 1;
		}
		if (flag == 1)
			return (print_error("check_permitted_char", ERR_MAP_CHAR));
	}
	return (i);
}

/**
 * @brief Checks the end of file. Spaces, tabs and new lines are accepted as
 * lines after the map reading. If any other char is found in a line, an
 * error is thrown
 *
 * @param fd file to read
 * @return int, end status,
 * 		0 for OK
 * 		-1 for error
 */
int	is_map_eof(int fd)
{
	char	*line;

	while (1)
	{
		line = strtrim_gnl(fd, "\t\n ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			free(line);
			return (print_error("check_eof", ERR_MAP_END));
		}
		free(line);
	}
	return (0);
}

char	*get_prefix(int i)
{
	const char	*prefix[WALL_SIDES + 2] = {"NO", "SO", "WE", "EA", "F", "C"};

	if (i < (WALL_SIDES + 2))
		return ((char *)prefix[i]);
	return (NULL);
}
