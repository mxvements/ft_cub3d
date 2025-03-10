/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:19 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/08 11:16:53 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	row_relative(t_cub *cub, float r)
{
	return ((cub->map->player->win_row - cub->minimap->start_x - \
		((MINIMAP_RADIUS * MINIMAP_PX) / 2) + r - \
		cub->minimap->start_x) / MINIMAP_PX);
}

static float	col_relative(t_cub *cub, float c)
{
	return ((cub->map->player->win_col - \
		((MINIMAP_RADIUS * MINIMAP_PX) / 2) + c) / MINIMAP_PX);
}

static int	minimap_choose_pixel(t_cub *cub, float r, float c)
{
	const t_minimap	*mini = cub->minimap;
	int				color;
	char			map_char;
	const float		row = row_relative(cub, r);
	const float		col = col_relative(cub, c);

	if (row < 0 || col < 0 || row >= cub->map->rows || col >= cub->map->cols)
		return (0);
	map_char = cub->map->map[(int)(row)][(int)(col)];
	if (map_char == ' ')
		color = 0x000000;
	else if (map_char == '1')
		color = 0x5d79a1;
	else if (map_char == '0')
		color = 0xdbbeaf;
	else if (map_char == 'N' || map_char == 'E' || map_char == 'S'
		|| map_char == 'W')
		color = 0xdbbeaf;
	else
		return (print_error("render_minimap", ERR_MAP_CHAR));
	put_pixel(c, r, color, cub);
	return (0);
}

int	minimap_render(t_cub *cub)
{
	t_minimap	*mini;
	int			r;
	int			c;

	mini = cub->minimap;
	r = -1 + cub->minimap->start_x;
	while (++r < WIN_HEIGHT)
	{
		c = -1;
		while (++c < MINIMAP_RADIUS * MINIMAP_PX)
		{
			put_pixel(c, r, 0x000000, cub);
			minimap_choose_pixel(cub, r, c);
		}
	}
	return (0);
}
