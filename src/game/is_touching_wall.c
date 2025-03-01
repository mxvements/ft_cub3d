#include "../includes/cub3d.h"

/**
 * @brief Check if a point is in a wall on the map.
 * 
 * This function checks if the given point ('pcol', 'prow') intersects a wall
 * by mapping the point in the corresponding map's tile and checking if it's
 * a wall ('1')
 * 
 * @param pcol column (x-coordinates) of the point
 * @param prow row (y-coorddinates) of the point
 * @param cub The game's context data structure
 * @return int 
 */
int	is_touching_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	i = ((prow - cub->minimap->start_x) / MINIMAP_PX);
	j = (pcol / MINIMAP_PX);
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

/**
 * @brief Calculates the horizontal offset where a ray intersects a wall
 * 
 * Computes the offset along the wall's texture based on the ray's
 * intersecction point in the world. The result is the relative position (in 
 * pixels) on the wall texture where the ray hit, which is used for texture
 * mapping.
 * 
 * It used the ray's intersection coordinates ('word_row', 'world_col') and 
 * adjusts based on the direction of the wall collision:
 * 	- For vertical collisions: offset calculated with 'world_col'
 * 	- For horizontal collisions: offset calculatd with 'world_row'
 * 
 * The function ensures the offset is wrapped within the bounds of the texture
 * size using the 'fmod' to handle edge ccases where the ray hits the wall 
 * multiple time within the same texture
 * 
 * @param cub The game's context data structure
 * @param i The index of the ray hit (window column)
 * @return float offset of the ray hit within the wall's texture, in pixels.
 */
float	wall_offset(t_cub *cub, int i)
{
	const float world_row = (cub->hits[i].ray[0] - cub->minimap->start_x);
	const float world_col = cub->hits[i].ray[1];
	const int	collistion_dir = cub->hits[i].collision_dir;
	float		offset;

	if (collistion_dir == VERTICAL)
		offset = fmod(world_col, MINIMAP_PX);
	else
		offset = fmod(world_row, MINIMAP_PX);
	return (offset);
}
