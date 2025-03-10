/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:49 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/08 11:35:25 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	texture_wall(t_cub *cub, int row[2], float wall_height, int i)
{
	const int	side = cub->hits[i].texture_idx;
	int			j;
	float		tex[2];
	int			color;
	float		offset;

	offset = (wall_offset(cub, i) / MINIMAP_PX);
	tex[0] = (int)round((wall_offset(cub, i) / MINIMAP_PX) * IMG_PX);
	j = row[0];
	while (row[1] > j)
	{
		tex[1] = (int)round((j - row[0]) * (IMG_PX / wall_height));
		if (side < 0 || side >= WALL_SIDES || ((tex[1] * IMG_PX) + tex[0]) < 0)
			color = 0x000000;
		else if (((tex[1] * IMG_PX) + tex[0]) > IMG_PX * IMG_PX - 1)
			color = cub->textures->text[side][(int)round(IMG_PX * IMG_PX - 1)];
		else
			color = cub->textures->text[side] \
				[(int)round((tex[1] * IMG_PX) + tex[0])];
		put_pixel(i, j, color, cub);
		j++;
	}
}

static void	put_line(t_cub *cub, int i)
{
	float	wall_height;
	int		row[2];

	if (cub->hits[i].dist < 0.01f)
		wall_height = (WIN_HEIGHT * MINIMAP_PX);
	else
		wall_height = (WIN_HEIGHT * MINIMAP_PX) / cub->hits[i].dist;
	row[0] = ((WIN_HEIGHT - wall_height) / 2);
	row[1] = (row[0] + wall_height);
	texture_ceiling(cub, row[0], i);
	texture_wall(cub, row, wall_height, i);
	texture_floor(cub, row[1], i);
}

void	put_perspective(t_cub *cub)
{
	t_player	*player;
	float		fraction;
	float		start_angle;
	int			screen_col_idx;

	player = cub->map->player;
	fraction = (cub->options.fov) / WIN_WIDTH;
	start_angle = player->angle - (cub->options.fov / 2);
	screen_col_idx = WIN_WIDTH;
	while (screen_col_idx > 0)
	{
		get_distance(cub, cos(start_angle), sin(start_angle), screen_col_idx);
		put_line(cub, screen_col_idx);
		start_angle += fraction;
		screen_col_idx--;
	}
}
