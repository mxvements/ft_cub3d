/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:38 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:39 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief main function to parse input from filepath to t_cub structures
 * The parsing has two parts: parse_texture_and_colors (first part of the file),
 * and parse_map. In case of error, file must be close and gnl must be cleaned
 * (it has static memory allocation) 
 * @param cub (t_cub *) main context structure of the project 
 * @param filepath (char *) argument referencing the file with the main data
 * @return int, status error: 0: ok, -1: parsing/initialiation error
 */
int	parse_input(t_cub *cub, char *filepath)
{
	t_map		*map;
	t_texture	*texture;

	map = cub->map;
	texture = cub->textures;
	cub->fd = open(filepath, O_RDONLY);
	if (cub->fd < 0)
		return (-1);
	if (parse_texture_and_colors(texture, cub->fd) < 0)
	{
		clean_gnl(cub->fd);
		close(cub->fd);
		return (-1);
	}
	if (parse_map(map, cub->fd) < 0)
	{
		clean_gnl(cub->fd);
		close(cub->fd);
		return (-1);
	}
	clean_gnl(cub->fd);
	close(cub->fd);
	return (0);
}
