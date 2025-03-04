#include "../includes/cub3d.h"

int	minimap_init(t_cub *cub)
{
	t_minimap	*mini;

	cub->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!cub->minimap)
		return (print_error("init_minimap", NULL));
	mini = cub->minimap;
	mini->start_x = WIN_HEIGHT - cub->map->rows * MINIMAP_PX;
	// mini->start_x = WIN_HEIGHT - (MINIMAP_RADIUS * MINIMAP_PX);
	// mini->end_y = MINIMAP_RADIUS * MINIMAP_PX;
	return (0);
}
