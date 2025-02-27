#include "../includes/cub3d.h"

static float	fix_fisheye(t_cub *cub, float delta_row, float delta_col,
		float d)
{
	float	angle;
	float	fixed_dist;

	// this distances has a fisheye effect
	if (d < 1.0f)
		return 0.99f;
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

static void	get_hit_side(t_cub *cub, int i, float prev_ray[2])
{
	int prev_tile[2];

	prev_tile[0] = (prev_ray[0] - cub->minimap->start_x) / MINIMAP_TILE;
	prev_tile[1] = prev_ray[1] / MINIMAP_TILE;

	if ((prev_tile[0] != cub->hits[i].map_tile[0]))
	{
		cub->hits[i].collision_dir = VERTICAL;
		if ((prev_tile[0] - cub->hits[i].map_tile[0]) > 0)
			cub->hits[i].texture_idx = NORTH; //0
		else
			cub->hits[i].texture_idx = SOUTH; //1
	}
	else if (prev_tile[1] != cub->hits->map_tile[1])
	{
		cub->hits[i].collision_dir = HORIZONTAL;
		if ((prev_tile[1] - cub->hits[i].map_tile[1]) > 0)
			cub->hits[i].texture_idx = WEST; //2
		else
			cub->hits[i].texture_idx = EAST; //3
	}
	// printf("side %i\n", cub->hits[i].texture_idx);
}

// get_hit, or get_collision
void	get_distance(t_cub *cub, float cos_f, float sin_f, int i)
{
	const t_player	*pl = cub->map->player;
	float prev_ray[2]; //[0] == row, [1] == col
	float ray[2];      //[0] == row, [1] == col
	const float	step = 0.02f;

	ray[0] = (float)pl->win_row;
	ray[1] = (float)pl->win_col;
	while (!is_touching_wall(ray[1], ray[0], cub))
	{
		prev_ray[0] = ray[0];
		prev_ray[1] = ray[1];
		ray[0] += cos_f * step;
		ray[1] += sin_f * step;
	}
	cub->hits[i].ray[0] = ray[0];
	cub->hits[i].ray[1] = ray[1];
	cub->hits[i].dist = distance(cub, (pl->win_row - ray[0]), (pl->win_col - ray[1]));
	cub->hits[i].map_tile[0] = (int)((ray[0] - cub->minimap->start_x) / MINIMAP_TILE);
	cub->hits[i].map_tile[1] = (int)(ray[1] / MINIMAP_TILE);
	cub->hits[i].angle = atan2(ray[1], ray[0]); // atan2(sin, cos)
	get_hit_side(cub, i, prev_ray);
	return ;
}
