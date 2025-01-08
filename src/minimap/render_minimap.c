#include "../includes/cub3d.h"

static char	*get_player_pos_str(t_player *player)
{
	char	*x;
	char	*y;
	char	*rslt;

	x = ft_itoa(player->x);
	if (!x)
		return (NULL);
	y = ft_itoa(player->y);
	if (!y)
		return (free(x), NULL);
	rslt = ft_concat("PLAYER AT: [", x, ",", y, "]", NULL);
	free(x);
	free(y);
	if (!rslt)
		return (NULL);
	// printf("concat result: %s\n", rslt);
	return (rslt);
}

static char	*get_player_dir_str(t_player *player)
{
	char	*x;
	char	*y;
	char	*rslt;

	x = ft_itoa(player->dirX);
	if (!x)
		return (NULL);
	y = ft_itoa(player->dirY);
	if (!y)
		return (free(x), NULL);
	rslt = ft_concat("VECTOR: [", x, ",", y, "]", NULL);
	free(x);
	free(y);
	if (!rslt)
		return (NULL);
	// printf("concat result: %s\n", rslt);
	return (rslt);
}

static void	put_str_to_win(t_cub *cub)
{
	const int	minimap_start_height = WIN_HEIGHT - cub->map->rows
			* MINIMAP_TILE_SIZE;
	const char	*str_position = get_player_pos_str(cub->map->player);
	const char	*str_vector = get_player_dir_str(cub->map->player);

	if (!str_position || !str_vector)
		return ;
	// print_player(cub->map->player);
	mlx_string_put(cub->mlx->mlx_ptr, cub->mlx->win, 0, minimap_start_height
		+ 16, 0xFF1100, (char *)str_position);
	mlx_string_put(cub->mlx->mlx_ptr, cub->mlx->win, 0, minimap_start_height
		+ 32, 0xFF1100, (char *)str_vector);
}

static void	put_img_to_win(t_cub *cub, void *img, int i, int j)
{
	const int	minimap_start_height = cub->minimap->start_x;
	
	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win, img, (j
			* MINIMAP_TILE_SIZE), (i * MINIMAP_TILE_SIZE
			+ minimap_start_height));
}

int	minimap_render(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map->map[++i])
	{
		j = -1;
		while (cub->map->map[i][++j])
		{
			if (cub->map->map[i][j] == ' ')
				put_img_to_win(cub, cub->minimap->img_void, i, j);
			else if (cub->map->map[i][j] == '1')
				put_img_to_win(cub, cub->minimap->img_wall, i, j);
			else if (cub->map->map[i][j] == '0')
				put_img_to_win(cub, cub->minimap->img_floor, i, j);
			else if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'E'
				|| cub->map->map[i][j] == 'S' || cub->map->map[i][j] == 'W')
				put_img_to_win(cub, cub->minimap->img_player, i, j);
			else
				return (print_error("render_minimap", ERR_MAP_CHAR));
		}
	}
	put_str_to_win(cub);
	return (0);
}
