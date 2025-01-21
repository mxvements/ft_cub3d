#include "../includes/cub3d.h"

int	minimap_set_img(t_cub *cub)
{
	t_minimap	*mini;
	int			img_size[2];

	mini = cub->minimap;
	img_size[0] = MINIMAP_TILE_SIZE;
	img_size[1] = MINIMAP_TILE_SIZE;
	mini->img_floor = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, MINI_F,
			&img_size[0], &img_size[1]);
	if (!mini->img_floor)
		return (print_error("set_img", ERR_MINI_IMG));
	mini->img_player = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, MINI_F,
			&img_size[0], &img_size[1]);
	if (!mini->img_player)
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

// static void	minimap_put_img_to_win(t_cub *cub, void *img, int i, int j)
// {
// 	const int	minimap_start_height = cub->minimap->start_x;
// 	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win, img, (j
// 			* MINIMAP_TILE_SIZE), (i * MINIMAP_TILE_SIZE
// 			+ minimap_start_height));
// }

int minimap_render(t_cub *cub)
{
    int i, j;
    t_minimap *mini = cub->minimap;

    i = -1;
    while (cub->map->map[++i])
    {
        j = -1;
        while (cub->map->map[i][++j])
        {
            int row = i * MINIMAP_TILE_SIZE + mini->start_x;
            int col = j * MINIMAP_TILE_SIZE;
            if (cub->map->map[i][j] == ' ')
                put_tile(cub, mini->img_void, col, row);
            else if (cub->map->map[i][j] == '1')
                put_tile(cub, mini->img_wall, col, row);
            else if (cub->map->map[i][j] == '0')
                put_tile(cub, mini->img_floor, col, row);
            else if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'E' ||
                     cub->map->map[i][j] == 'S' || cub->map->map[i][j] == 'W')
                put_tile(cub, mini->img_player, col, row);
            else
                return (print_error("render_minimap", ERR_MAP_CHAR));
        }
    }
    return (0);
}
