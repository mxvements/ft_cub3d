#include "../includes/cub3d.h"

int	touch_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	i = (prow - cub->minimap->start_x) / MINIMAP_TILE_SIZE;
	j = pcol / MINIMAP_TILE_SIZE;
	if (i < 0 || i >= cub->map->rows || j < 0 || j >= cub->map->cols)
		return (1); // Treat out-of-bounds as a wall
	if (cub->map->map[i][j] == '1')
		return (1);
	return (0);
}
static float	distance(float row2, float row1, float col2, float col1,
		t_cub *cub)
{
	float	delta_row;
	float	delta_col;
	float	distance;
	float	angle;
	float	fix_distance;

	delta_row = (row1 - row2);
	delta_col = (col1 - col2);
	distance = sqrt(delta_row * delta_row + delta_col * delta_col);
	// Distance: %f\n", row1, col1, row2, col2, distance);
	// this distances has a fisheye effect this fix
	angle = atan2(delta_col, delta_row) - cub->map->player->angle;
	// POSIBLE BUG
	fix_distance = fabs(distance * cos(angle));
	// printf("dist: %f, fixed: %f\n", distance, fix_distance);
	return (fix_distance);
}
void	put_line(t_player *player, t_cub *cub, float angle, int i, int color)
{
	float		cos_angle;
	float		sin_angle;
	const float	player_row = player->map_x * MINIMAP_TILE_SIZE
			+ cub->minimap->start_x + MINIMAP_TILE_SIZE / 2;
	const float	player_col = player->map_y * MINIMAP_TILE_SIZE
			+ MINIMAP_TILE_SIZE / 2;
	float		ray_row;
	float		ray_col;
	float		dist;
	float		wall_height;
	float		start_row;
	float		end_row;
	int			y;

	// perspective
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	ray_row = (float)player_row;
	ray_col = (float)player_col;
	// FOV on minimap
	while (!touch_wall(ray_col, ray_row, cub))
	{
		if (cub->options.show_minimap == 1)
			put_pixel((int)ray_col, (int)ray_row, 0xAA6666, cub);
		ray_row += cos_angle;
		ray_col += sin_angle;
	}
	// perspective
	dist = distance(ray_row, player_row, ray_col, player_col, cub);
	if (dist >= 0.1)
		wall_height = ((WIN_HEIGHT * 16) / (float)dist);
	else
		wall_height = (WIN_HEIGHT * 16);
	start_row = ((WIN_HEIGHT - wall_height) / 2);
	end_row = (start_row + wall_height);
	y = end_row;
	while (y >= start_row)
	{
		// antialiasing
		put_pixel(i, y, color, cub);
		y--;
	}
}

void	minimap_put_axis(t_cub *cub, int color)
{
	t_player	*player;
	float		ray_row;
	float		ray_col;
	float		cos_angle;
	float		sin_angle;

	// printf("minimap_put_axis\n");
	player = cub->map->player;
	ray_row = player->map_x * MINIMAP_TILE_SIZE + cub->minimap->start_x
		+ MINIMAP_TILE_SIZE / 2;
	ray_col = player->map_y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	while (!touch_wall(ray_col, ray_row, cub))
	{
		if (cub->options.show_minimap == 1)
			put_pixel((int)ray_col, (int)ray_row, color, cub);
		ray_row += cos_angle;
		ray_col += sin_angle;
	}
}
void	put_camera(t_cub *cub)
{
	t_player	*player;
	const float	FOV = PI / 6;
	float		fraction;
	float		start_angle;
	int			screen_col_idx;

	player = cub->map->player;
	fraction = (FOV * 2) / WIN_WIDTH;
	//(FOV * 2) / (cub->map->cols * MINIMAP_TILE_SIZE)
	start_angle = player->angle - FOV;
	screen_col_idx = WIN_WIDTH;
	// i < (cub->map->cols * MINIMAP_TILE_SIZE)
	while (screen_col_idx > 0)
	{
		put_line(player, cub, start_angle, screen_col_idx, 255);
		start_angle += fraction;
		screen_col_idx--;
	}
}
