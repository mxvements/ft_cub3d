/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:16 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:17 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	sum_player_relative_position(t_cub *cub, float *r, float *c)
{
	*r += (cub->minimap->start_x + ((MINIMAP_RADIUS * MINIMAP_PX) / 2));
	*c += (((MINIMAP_RADIUS * MINIMAP_PX) / 2));
}

static int	is_on_minimap_bounds(t_cub *cub, float r, float c)
{
	if (r < cub->minimap->start_x || r  >= WIN_HEIGHT)
		return (0);
	if (c < 0 || c >= (MINIMAP_RADIUS * MINIMAP_PX))
		return (0);
	return (1);
}

void	minimap_put_player(t_cub *cub, int color)
{
	t_player	*player;
	float		start_row;
	float		start_col;

	player = cub->map->player;
	start_row = -(MINIMAP_PX / 4);
	start_col = -(MINIMAP_PX / 4);
	sum_player_relative_position(cub, &start_row, &start_col);
	put_square(start_col, start_row, color, cub);
}

void	minimap_put_fov(t_cub *cub, int color_fov)
{
	const float	fraction = (cub->options.fov) / WIN_WIDTH;
	float		start_angle;
	int			screen_col_idx;
	float		ray[2];
	float		px[2];

	start_angle = cub->map->player->angle - (cub->options.fov / 2);
	screen_col_idx = WIN_WIDTH;
	while (screen_col_idx > 0)
	{
		ray[0] = (float)cub->map->player->win_row;
		ray[1] = (float)cub->map->player->win_col;
		while (!is_touching_wall(ray[1], ray[0], cub))
		{
			px[0] = (ray[0] - cub->map->player->win_row);
			px[1] = (ray[1] - cub->map->player->win_col);
			sum_player_relative_position(cub, &px[0], &px[1]);
			if (is_on_minimap_bounds(cub, px[0], px[1]))
				put_pixel((int)floor(px[1]), (int)floor(px[0]), color_fov, cub);
			ray[0] += cos(start_angle);
			ray[1] += sin(start_angle);
		}
		start_angle += fraction;
		screen_col_idx--;
	}
}

void	minimap_put_axis(t_cub *cub, int color_axis)
{
	t_player	*player;
	float		ray[2];
	float		px[2];

	player = cub->map->player;
	ray[0] = cub->map->player->win_row;
	ray[1] = cub->map->player->win_col;
	while (!is_touching_wall(ray[1], ray[0], cub))
	{
		px[0] = (ray[0] - cub->map->player->win_row);
		px[1] = (ray[1] - cub->map->player->win_col);
		sum_player_relative_position(cub, &px[0], &px[1]);
		if (is_on_minimap_bounds(cub, px[0], px[1]))
			put_pixel((int)floor(px[1]), (int)floor(px[0]), color_axis, cub);
		ray[0] += cos(player->angle);
		ray[1] += sin(player->angle);
	}
}
