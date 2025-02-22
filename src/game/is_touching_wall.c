#include "../includes/cub3d.h"

int	is_touching_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	i = (prow - cub->minimap->start_x) / MINIMAP_TILE;
	j = pcol / MINIMAP_TILE;
	if (i < 0 || i >= cub->map->rows || j < 0 || j >= cub->map->cols)
		return (1); // Treat out-of-bounds as a wall
	if (cub->map->map[i][j] == '1')
		return (1);
	return (0);
}
