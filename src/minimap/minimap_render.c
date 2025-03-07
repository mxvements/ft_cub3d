/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:19 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:20 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//TODO: delete this
int	minimap_set_img(t_cub *cub)
{
	t_minimap	*mini;
	int			img_size[2];

	mini = cub->minimap;
	img_size[0] = MINIMAP_PX;
	img_size[1] = MINIMAP_PX;
	mini->img_floor = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, MINI_F,
			&img_size[0], &img_size[1]);
	if (!mini->img_floor)
		return (print_error("set_img", ERR_MINI_IMG));
	mini->img_void = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, MINI_V,
			&img_size[0], &img_size[1]);
	if (!mini->img_void)
		return (print_error("set_img", ERR_MINI_IMG));
	mini->img_wall = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, MINI_W,
			&img_size[0], &img_size[1]);
	if (!mini->img_wall)
		return (print_error("set_img", ERR_MINI_IMG));
	return (0);
}

// static int	minimap_choose_tile(t_cub *cub, int i, int j)
// {
// 	const t_minimap	*mini = cub->minimap;
// 	const int		row = (i - cub->map->player->map_row + MINIMAP_RADIUS / 2)
// 				* MINIMAP_PX + mini->start_x;
// 	const int		col = (j - cub->map->player->map_col + MINIMAP_RADIUS / 2)
// 				* MINIMAP_PX;
// 	if (cub->map->map[i][j] == ' ')
// 		put_partial_tile(cub, mini->img_void, col, row);
// 	else if (cub->map->map[i][j] == '1')
// 		put_partial_tile(cub, mini->img_wall, col, row);
// 	else if (cub->map->map[i][j] == '0')
// 		put_partial_tile(cub, mini->img_floor, col, row);
// 	else if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'E'
// 		|| cub->map->map[i][j] == 'S' || cub->map->map[i][j] == 'W')
// 	{
// 		if (cub->map->old_char == '0')
// 			put_partial_tile(cub, mini->img_floor, col, row);
// 		else if (cub->map->old_char == '1')
// 			put_partial_tile(cub, mini->img_wall, col, row);
// 		else
// 			return (print_error("render_minimap", ERR_MAP_CHAR));
// 	}
// 	else
// 		return (print_error("render_minimap", ERR_MAP_CHAR));
// 	return (0);
// }

static int	minimap_choose_pixel(t_cub *cub, float r, float c)
{
	const t_minimap	*mini = cub->minimap;
	int				color;
	char			map_char;
	const float		row = (cub->map->player->win_row - cub->minimap->start_x - ((MINIMAP_RADIUS * MINIMAP_PX) / 2) + r - cub->minimap->start_x) / MINIMAP_PX;
	const float		col = (cub->map->player->win_col - ((MINIMAP_RADIUS * MINIMAP_PX) / 2) + c) / MINIMAP_PX;

	if (row < 0 || col < 0 || row >= cub->map->rows || col >= cub->map->cols)
		return (0);
	map_char = cub->map->map[(int)(row)][(int)(col)];
	// get color from map
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
	// put pixel
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
