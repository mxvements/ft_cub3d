#include "../includes/cub3d.h"

static float	fix_fisheye(t_cub *cub, float delta_row, float delta_col,
		float d)
{
	float	angle;
	float	fixed_dist;

	// this distances has a fisheye effect
	angle = atan2(delta_col, delta_row) - cub->map->player->angle;
	// POSIBLE BUG on a atan2
	fixed_dist = fabs(d * cos(angle));
	// printf("dist: %f, fixed: %f\n", distance, fix_distance);
	return (fixed_dist);
}

static float	distance(t_cub *cub, float delta_row, float delta_col)
{
	float	dist;

	dist = sqrt(delta_row * delta_row + delta_col * delta_col);
	dist = fix_fisheye(cub, delta_row, delta_col, dist);
	return (dist);
}

void	get_distance(t_cub *cub, float cos, float sin, int i)
{
	const t_player	*pl = cub->map->player;
	float			ray_row;
	float			ray_col;

	ray_row = (float)pl->win_row;
	ray_col = (float)pl->win_col;
	while (!is_touching_wall(ray_col, ray_row, cub))
	{
		ray_row += cos;
		ray_col += sin;
	}
	cub->dist[i]  = distance(cub, (pl->win_row - ray_row), (pl->win_col - ray_col));
	return ;
}
