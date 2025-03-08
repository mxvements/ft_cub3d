/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_touching_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:36 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/08 15:32:40 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_touching_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	i = (int)((prow - cub->minimap->start_x) / MINIMAP_PX);
	j = (int)(pcol / MINIMAP_PX);
	if (i < 0 || i >= cub->map->rows || j < 0 || j >= cub->map->cols)
		return (1);
	if (cub->map->map[i][j] == '1')
		return (1);
	return (0);
}

void	texture_ceiling(t_cub *cub, int start_row, int i)
{
	int	k;

	k = 0;
	while (k <= start_row)
	{
		put_pixel(i, k, cub->textures->ceiling, cub);
		k++;
	}
}

void	texture_floor(t_cub *cub, int end_row, int i)
{
	int	k;

	k = end_row;
	while (k <= WIN_WIDTH)
	{
		put_pixel(i, k, cub->textures->floor, cub);
		k++;
	}
}

float	wall_offset(t_cub *cub, int i)
{
	const float	world_row = (cub->hits[i].ray[0] - cub->minimap->start_x);
	const float	world_col = cub->hits[i].ray[1];
	const int	collistion_dir = cub->hits[i].collision_dir;
	float		offset;

	if (collistion_dir == VERTICAL)
		offset = fmod(world_col, MINIMAP_PX);
	else
		offset = fmod(world_row, MINIMAP_PX);
	return (offset);
}
