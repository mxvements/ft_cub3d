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
	const int		row = i * MINIMAP_PX + mini->start_x;
	const int		col = j * MINIMAP_PX;

	if (cub->map->map[i][j] == ' ')
		put_tile(cub, mini->img_void, col, row);
	else if (cub->map->map[i][j] == '1')
		put_tile(cub, mini->img_wall, col, row);
	else if (cub->map->map[i][j] == '0')
		put_tile(cub, mini->img_floor, col, row);
	else if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'E'
		|| cub->map->map[i][j] == 'S' || cub->map->map[i][j] == 'W')
	{
		if (cub->map->old_char == '0')
			put_tile(cub, mini->img_floor, col, row);
		else if (cub->map->old_char == '1')
			put_tile(cub, mini->img_wall, col, row);
		else
			return (print_error("render_minimap", ERR_MAP_CHAR));
	}
	else
		return (print_error("render_minimap", ERR_MAP_CHAR));
	return (0);
}

static int minimap_bounds(int value)
{
	float result;
	result = (int)round(value - MINIMAP_RADIUS);
	if (result < 0)
		return (0);
	return (result);
}

int	minimap_render(t_cub *cub)
{
	t_minimap	*mini;
	int			i;
	int			j;
	int			start[2];
	int			end[2];

	mini = cub->minimap;
	start[0] = 0;//minimap_bounds(cub->map->player->map_row - MINIMAP_RADIUS);
	// start[1] = minimap_bounds(cub->map->player->map_col - MINIMAP_RADIUS);
	end[0] = 0;//minimap_bounds(cub->map->player->map_row + MINIMAP_RADIUS);
	// end[1] = minimap_bounds(cub->map->player->map_col + MINIMAP_RADIUS);
	i = start[0] - 1;
	while (cub->map->map[++i]) //&&  i <= end[0])
	{
		j = start[1] - 1;
		while (cub->map->map[i][++j])// && j <= end[1])
		{
			if (i >= 0 && i < cub->map->rows && j>= 0 && j < cub->map->cols)
				minimap_choose_tile(cub, i, j);
		}
	}
	return (0);
}
