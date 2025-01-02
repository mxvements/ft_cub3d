#include "../includes/cub3d.h"

int	init_minimap(t_cub *cub)
{
	t_minimap	*minimap;
	int			img_size[2];

	cub->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!cub->minimap)
		return (print_error("init_minimap", NULL));
	minimap = cub->minimap;
	img_size[0] = IMG_SIZE_X;
	img_size[1] = IMG_SIZE_Y;
	minimap->path_wall = MINIMAP_WALL;
	minimap->path_floor = MINIMAP_FLOOR;
	minimap->path_player = MINIMAP_PLAYER;
	minimap->img_wall = mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
			minimap->path_wall, &img_size[0], &img_size[1]);
	minimap->img_floor = mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
			minimap->path_floor, &img_size[0], &img_size[1]);
	minimap->img_player = mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
			minimap->path_player, &img_size[0], &img_size[1]);
	cub->minimap = minimap;
	return (0);
}
