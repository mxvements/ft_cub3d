#include "../includes/cub3d.h"

int	is_touching_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	i = ((prow - cub->minimap->start_x) / MINIMAP_TILE);
	j = (pcol / MINIMAP_TILE);
	if (cub->map->map[i][j] == '1')
		return (1);
	if (i < 0 || i >= cub->map->rows || j < 0 || j >= cub->map->cols)
		return (1);
	return (0);
}

void	texture_ceiling(t_cub *cub, int start_row, int i)
{
	int	k;

	k = 0;
	while (k <= start_row)
	{
		put_pixel(i, k, cub->textures->ceiling, cub);
		k++;
	}
}

void	texture_floor(t_cub *cub, int end_row, int i)
{
	int	k;

	k = end_row;
	while (k <= WIN_WIDTH)
	{
		put_pixel(i, k, cub->textures->floor, cub);
		k++;
	}
}

float	wall_offset(t_cub *cub, int i)
{
	const float world_row = (cub->hits[i].ray[0] - cub->minimap->start_x);
	const float world_col = cub->hits[i].ray[1];
	const int	collistion_dir = cub->hits[i].collision_dir;
	float		offset;

	if (collistion_dir == VERTICAL)
		offset = fmod(world_col, MINIMAP_TILE);
	else
		offset = fmod(world_row, MINIMAP_TILE);
	return (offset);
}
