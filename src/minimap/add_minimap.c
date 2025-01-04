#include "../includes/cub3d.h"

static void	put_img_to_win(t_cub *cub, void *img, int i, int j)
{
	const int	minimap_start_height = WIN_HEIGHT - cub->map->rows
			* MINIMAP_IMG_SIZE_Y;

	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win, img, (j
			* MINIMAP_IMG_SIZE_X), (i * MINIMAP_IMG_SIZE_Y
			+ minimap_start_height));
}
static char	*ft_concat(char *first, ...)
{
	va_list	vargs;
	char	*current;
	char	*tmp;
	char	*rslt;

	va_start(vargs, first);
	rslt = ft_strdup(first);
	if (!rslt)
		return (NULL);
	current = va_arg(vargs, char *);
	while (current)
	{
		// printf("current: %s\n", current);
		tmp = ft_strdup(rslt);
		if (!tmp)
			return (NULL);
		free(rslt);
		rslt = ft_strjoin(tmp, current);
		if (!rslt)
			return (free(tmp), NULL);
		free(tmp);
		current = va_arg(vargs, char *);
	}
	va_end(vargs);
	return (rslt);
}

static char	*get_player_pos_str(t_player *player)
{
	const char	*x = ft_itoa(player->x);
	const char	*y = ft_itoa(player->y);
	char		*rslt;

	rslt = ft_concat("PLAYER AT: [", x, ",", y, "]");
	if (!rslt)
		return (NULL);
	// printf("concat result: %s\n", rslt);
	return (rslt);
}

static char	*get_player_dir_str(t_player *player)
{
	const char	*x = ft_itoa((int)player->dirX);
	const char	*y = ft_itoa((int)player->dirY);
	char		*rslt;

	rslt = ft_concat("VECTOR : [", x, ",", y, "]");
	if (!rslt)
		return (NULL);
	// printf("concat result: %s\n", rslt);
	return (rslt);
}
static void	put_str_to_win(t_cub *cub)
{
	const int	minimap_start_height = WIN_HEIGHT - cub->map->rows
			* MINIMAP_IMG_SIZE_Y;
	const char	*str_position = get_player_pos_str(cub->map->player);
	const char	*str_vector = get_player_dir_str(cub->map->player);

	if (!str_position || !str_vector)
		return ;
	print_player(cub->map->player);
	mlx_string_put(cub->mlx->mlx_ptr, cub->mlx->win, 0, minimap_start_height
		+ 16, 0xFF1100, (char *)str_position);
	mlx_string_put(cub->mlx->mlx_ptr, cub->mlx->win, 0, minimap_start_height
		+ 32, 0xFF1100, (char *)str_vector);
}

int	minimap_render(t_cub *cub)
{
	int		i;
	int		j;
	char	**map;

	map = cub->map->map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
				put_img_to_win(cub, cub->minimap->img_void, i, j);
			else if (map[i][j] == '1')
				put_img_to_win(cub, cub->minimap->img_wall, i, j);
			else if (map[i][j] == '0')
				put_img_to_win(cub, cub->minimap->img_floor, i, j);
			else if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S'
				|| map[i][j] == 'W')
				put_img_to_win(cub, cub->minimap->img_player, i, j);
			else
				return (print_error("render_minimap", ERR_MAP_CHAR));
		}
	}
	put_str_to_win(cub);
	return (0);
}

int	add_minimap(t_cub *cub)
{
	if (minimap_init(cub) < 0)
		return (-1);
	if (minimap_render(cub) < 0)
		return (-1);
	return (0);
}
