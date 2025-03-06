#include "../includes/cub3d.h"

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

static int	minimap_choose_tile(t_cub *cub, int i, int j)
{
	const t_minimap	*mini = cub->minimap;
	const int		row = (i - cub->map->player->map_row + MINIMAP_RADIUS / 2)
				* MINIMAP_PX + mini->start_x;
	const int		col = (j - cub->map->player->map_col + MINIMAP_RADIUS / 2)
				* MINIMAP_PX;

	if (cub->map->map[i][j] == ' ')
		put_partial_tile(cub, mini->img_void, col, row);
	else if (cub->map->map[i][j] == '1')
		put_partial_tile(cub, mini->img_wall, col, row);
	else if (cub->map->map[i][j] == '0')
		put_partial_tile(cub, mini->img_floor, col, row);
	else if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'E'
		|| cub->map->map[i][j] == 'S' || cub->map->map[i][j] == 'W')
	{
		if (cub->map->old_char == '0')
			put_partial_tile(cub, mini->img_floor, col, row);
		else if (cub->map->old_char == '1')
			put_partial_tile(cub, mini->img_wall, col, row);
		else
			return (print_error("render_minimap", ERR_MAP_CHAR));
	}
	else
		return (print_error("render_minimap", ERR_MAP_CHAR));
	return (0);
}

// static int minimap_bounds(int value)
// {
// 	float result;
// 	result = (int)round(value - MINIMAP_RADIUS);
// 	if (result < 0)
// 		return (0);
// 	return (result);
// }

static int	minimap_choose_pixel(t_cub *cub, int i, int j)
{
	const t_minimap	*mini = cub->minimap;
	const float		row = (cub->map->player->win_row - i + cub->minimap->start_x) / IMG_PX;
	const float		col = (cub->map->player->win_col - j) / IMG_PX;
	char			map_char;

	printf("row, col: %f, %f\n", row, col);
	map_char = cub->map->map[(int)(row) ][(int)(col)];
	printf("map_char: %c\n", map_char);
	if (map_char == ' ')
		put_pixel(j, i, 0x000000, cub);
	else if (map_char == '1')
		put_pixel(j, i, 0x992200, cub);
	else if (map_char == '0')
		put_pixel(j, i, 0x1133FF, cub);
	else if (map_char == 'N' || map_char == 'E' || map_char == 'S'
		|| map_char == 'W')
	{
		if (cub->map->old_char == '0')
			put_pixel(j, i, 0x0000AA, cub);
		else if (cub->map->old_char == '1')
			put_pixel(j, i, 0x00AA00, cub);
		else
			return (print_error("render_minimap", ERR_MAP_CHAR));
	}
	else
		return (print_error("render_minimap", ERR_MAP_CHAR));
	return (0);
}

int	minimap_render(t_cub *cub)
{
	t_minimap	*mini;
	int			i;
	int			j;
	int			start[2];
	int			end[2];
	float		r;
	float		c;

	mini = cub->minimap;
	// start[0] = minimap_bounds(cub->map->player->map_row - MINIMAP_RADIUS);
	// start[1] = minimap_bounds(cub->map->player->map_col - MINIMAP_RADIUS);
	// end[0] = minimap_bounds(cub->map->player->map_row + MINIMAP_RADIUS);
	// end[1] = minimap_bounds(cub->map->player->map_col + MINIMAP_RADIUS);
	// i = - MINIMAP_RADIUS/2 - 1;
	// while (++i < MINIMAP_RADIUS/2) //&&  i <= end[0])
	// {
	// 	j =  - MINIMAP_RADIUS / 2 - 1;
	// 	while (++j < MINIMAP_RADIUS / 2)// && j <= end[1])
	// 	{
	// 		//el x e i son los relativos al jugador
	// 		r = cub->map->player->win_row +(i * MINIMAP_PX); //-i;
	// 		c = cub->map->player->win_col + (j * MINIMAP_PX);
	// 		if (r < 0)
	// 			r = 0;
	// 		if (c < 0)
	// 			c = 0;
	// 		if (r > cub->map->rows *  MINIMAP_PX)
	// 			r = cub->map->rows * MINIMAP_PX;
	// 		if (c > cub->map->cols)
	// 			c = cub->map->cols;
	// 		if (cub->map->map[r][c])
	// 			minimap_choose_tile(cub, r, c);
	// 		// else
	// 			// put_tile(cub, mini->img_void, i * MINIMAP_PX, j * MINI);
	// 	}
	// }
	i = -1 + cub->minimap->start_x;
	while (++i < MINIMAP_RADIUS * MINIMAP_PX + cub->minimap->start_x)
	{
		j = -1;
		while (++j < MINIMAP_RADIUS * MINIMAP_PX)
		{
			minimap_choose_pixel(cub, i, j);
		}
	}
	return (0);
}
