#include "../includes/cub3d.h"

/*
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
}*/

// static int	add_path(char **set_path, char *path)
// {
// 	int	img_size[2];

// 	img_size[0] = MINIMAP_TILE_SIZE;
// 	img_size[1] = MINIMAP_TILE_SIZE;
// 	*set_path = ft_strdup(path);
// 	if (!*set_path)
// 		return (print_error("add_path", NULL));
// 	return (0);
// }

int	minimap_init(t_cub *cub)
{
	t_minimap	*mini;

	cub->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!cub->minimap)
		return (print_error("init_minimap", NULL));
	mini = cub->minimap;
	mini->start_x = WIN_HEIGHT - cub->map->rows * MINIMAP_TILE;

	// if (add_path(&mini->path_floor, MINI_F) < 0)
	// 	return (-1);
	// if (add_path(&mini->path_wall, MINI_W) < 0)
	// 	return (-1);
	// if (add_path(&mini->path_player, MINI_PLF) < 0)
	// 	return (-1);
	// if (add_path(&mini->path_void, MINI_V) < 0)
	// 	return (-1);
	
	return (0);
}

// int	add_minimap(t_cub *cub)
// {
// 	if (minimap_init(cub) < 0)
// 		return (-1);
// 	// if (minimap_render(cub) < 0)
// 	// 	return (-1);
// 	return (0);
// }
