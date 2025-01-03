#include "../includes/cub3d.h"

static int	init_minimap(t_cub *cub)
{
	t_minimap	*minimap;
	int			img_size[2];

	cub->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!cub->minimap)
		return (print_error("init_minimap", NULL));
	minimap = cub->minimap;
	img_size[0] = MINIMAP_IMG_SIZE_X;
	img_size[1] = MINIMAP_IMG_SIZE_Y;
	minimap->path_wall = MINIMAP_WALL;
	minimap->path_floor = MINIMAP_FLOOR;
	minimap->path_player = MINIMAP_PLAYER_F;
	minimap->path_void = MINIMAP_VOID;
	minimap->img_wall = mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
			minimap->path_wall, &img_size[0], &img_size[1]);
	minimap->img_floor = mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
			minimap->path_floor, &img_size[0], &img_size[1]);
	minimap->img_player = mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
			minimap->path_player, &img_size[0], &img_size[1]);
	minimap->img_void = mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
			minimap->path_void, &img_size[0], &img_size[1]);
	cub->minimap = minimap;
	return (0);
}
static void	put_img_to_win(t_cub *cub, void *img, int i, int j)
{
	const int	minimap_start_height = WIN_HEIGHT - cub->map->rows
			* MINIMAP_IMG_SIZE_Y;
	const t_mlx	*mlx = cub->mlx;

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img, (j
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
	printf("current: %s\n", current);
	while (current)
	{
		tmp = ft_strdup(rslt);
		if (!tmp)
			return (NULL);
		free(rslt);
		rslt = ft_strjoin(tmp, current);
		if (!rslt)
			return (free(tmp), NULL);
		free(tmp);
		current = va_arg(vargs, char *);
		printf("current: %s\n", current);
	}
	va_end(vargs);
	return (rslt);
}

static char	*get_player_pos_str(t_player *player)
{
	const char	*x = ft_itoa(player->x);
	const char	*y = ft_itoa(player->y);
	char		*rslt;

	rslt = ft_concat("PLAYER AT: [", x, ",", y, "]\n");
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

	rslt = ft_concat("VECTOR : [", x, ",", y, "]\n");
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

int	render_minimap(t_cub *cub)
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
	if (init_minimap(cub) < 0)
		return (-1);
	if (render_minimap(cub) < 0)
		return (-1);
	return (0);
}
