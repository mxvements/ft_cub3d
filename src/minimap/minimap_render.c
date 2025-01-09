#include "../includes/cub3d.h"

static void	minimap_put_img_to_win(t_cub *cub, void *img, int i, int j)
{
	const int	minimap_start_height = cub->minimap->start_x;

	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win, img, (j
			* MINIMAP_TILE_SIZE), (i * MINIMAP_TILE_SIZE
			+ minimap_start_height));
}

static int	minimap_set_img(t_cub *cub)
{
	t_minimap	*mini;
	int			img_size[2];

	mini = cub->minimap;
	img_size[0] = MINIMAP_TILE_SIZE;
	img_size[1] = MINIMAP_TILE_SIZE;
	mini->img_floor = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, mini->path_floor,
			&img_size[0], &img_size[1]);
	if (mini->img_floor)
		return (print_error("set_img", ERR_MINI_IMG));
	mini->img_player = mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
			mini->path_player, &img_size[0], &img_size[1]);
	if (mini->img_floor)
		return (print_error("set_img", ERR_MINI_IMG));
	mini->img_void = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, mini->path_void,
			&img_size[0], &img_size[1]);
	if (mini->img_floor)
		return (print_error("set_img", ERR_MINI_IMG));
	mini->img_wall = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, mini->path_wall,
			&img_size[0], &img_size[1]);
	if (mini->img_floor)
		return (print_error("set_img", ERR_MINI_IMG));
	return (0);
}

int	minimap_render(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	minimap_set_img(cub);
	while (cub->map->map[++i])
	{
		j = -1;
		while (cub->map->map[i][++j])
		{
			if (cub->map->map[i][j] == ' ')
				minimap_put_img_to_win(cub, cub->minimap->img_void, i, j);
			else if (cub->map->map[i][j] == '1')
				minimap_put_img_to_win(cub, cub->minimap->img_wall, i, j);
			else if (cub->map->map[i][j] == '0')
				minimap_put_img_to_win(cub, cub->minimap->img_floor, i, j);
			else if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'E'
				|| cub->map->map[i][j] == 'S' || cub->map->map[i][j] == 'W')
				minimap_put_img_to_win(cub, cub->minimap->img_player, i, j);
			else
				return (print_error("render_minimap", ERR_MAP_CHAR));
		}
	}
	minimap_put_str(cub);
	return (0);
}
