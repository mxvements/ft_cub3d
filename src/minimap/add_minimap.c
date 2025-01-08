#include "../includes/cub3d.h"

// util function, to add to libft
char	*ft_concat(char *first, ...)
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
			return (free(rslt), NULL);
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

static void	*set_img(t_cub *cub, char **set_path, char *path, void *set_img)
{
	int	img_size[2];

	img_size[0] = MINIMAP_TILE_SIZE;
	img_size[1] = MINIMAP_TILE_SIZE;
	*set_path = ft_strdup(path);
	if (!*set_path)
		return (NULL);
	set_img = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, *set_path, &img_size[0],
			&img_size[1]);
	return (set_img);
}

int	minimap_init(t_cub *cub)
{
	t_minimap	*mini;

	cub->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!cub->minimap)
		return (print_error("init_minimap", NULL));
	mini = cub->minimap;
	mini->start_x = WIN_HEIGHT - cub->map->rows * MINIMAP_TILE_SIZE;
	mini->img_floor = set_img(cub, &mini->path_floor, MINI_F, mini->img_floor);
	if (!mini->img_floor)
		return (print_error("init_minimap", ERR_MINI_IMG));
	mini->img_wall = set_img(cub, &mini->path_wall, MINI_W, mini->img_wall);
	if (!mini->img_wall)
		return (print_error("init_minimap", ERR_MINI_IMG));
	mini->img_player = set_img(cub, &mini->path_player, MINI_PLF,
			mini->img_player);
	if (!mini->img_player)
		return (print_error("init_minimap", ERR_MINI_IMG));
	mini->img_void = set_img(cub, &mini->path_void, MINI_V, mini->img_void);
	if (!mini->img_void)
		return (print_error("init_minimap", ERR_MINI_IMG));
	return (0);
}

int	add_minimap(t_cub *cub)
{
	if (minimap_init(cub) < 0)
		return (-1);
	// if (minimap_render(cub) < 0)
	// 	return (-1);
	return (0);
}
