#include "../includes/cub3d.h"

int	minimap_set_img(t_cub *cub)
{
	t_minimap	*mini;
	int			img_size[2];

	mini = cub->minimap;
	img_size[0] = MINIMAP_TILE;
	img_size[1] = MINIMAP_TILE;
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
	// print_minimap(mini);
	return (0);
}
static int	minimap_choose_tile(t_cub *cub, int i, int j)
{
	const t_minimap	*mini = cub->minimap;
	const int		row = i * MINIMAP_TILE + mini->start_x;
	const int		col = j * MINIMAP_TILE;

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

int	minimap_render(t_cub *cub)
{
	t_minimap	*mini;

	int i, j;
	mini = cub->minimap;
	i = -1;
	while (cub->map->map[++i])
	{
		j = -1;
		while (cub->map->map[i][++j])
		{
			minimap_choose_tile(cub, i, j);
		}
	}
	return (0);
}

/* ----------------------------------------------------------------------- */


void	minimap_put_fov(t_cub *cub, int color_fov)
{
	float	fraction;
	float	start_angle;
	int		screen_col_idx;
	float	ray_row;
	float	ray_col;

	fraction = (cub->options.fov * 3) / WIN_WIDTH;
	start_angle = cub->map->player->angle - cub->options.fov;
	screen_col_idx = WIN_WIDTH;
	while (screen_col_idx > 0)
	{
		ray_row = (float)cub->map->player->win_row;
		ray_col = (float)cub->map->player->win_col;
		while (!is_touching_wall(ray_col, ray_row, cub)
			&& cub->options.show_minimap == 1)
		{
			put_pixel((int)ray_col, (int)ray_row, color_fov, cub);
			ray_row += cos(start_angle);
			ray_col += sin(start_angle);
		}
		start_angle += fraction;
		screen_col_idx--;
	}
}

/* ----------------------------------------------------------------------- */

void	minimap_put_axis(t_cub *cub, int color_axis)
{
	t_player	*player;
	float		ray_row;
	float		ray_col;
	float		cos_angle;
	float		sin_angle;

	// printf("minimap_put_axis\n");
	player = cub->map->player;
	ray_row = cub->map->player->win_row;
	ray_col = cub->map->player->win_col;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	while (!is_touching_wall(ray_col, ray_row, cub)
		&& cub->options.show_minimap == 1)
	{
		put_pixel((int)ray_col, (int)ray_row, color_axis, cub);
		ray_row += cos_angle; // cos(player->angle)
		ray_col += sin_angle; // sin(player->angle)
	}
}
